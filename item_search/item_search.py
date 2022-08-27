import json
import os

def setup(filename):

    # Create global variables for ease of usage.
    global objectives
    objectives = {}
    global locations
    locations = []

    with open(filename) as level_data:

        # Make data readable by python.
        data_json = level_data.read()
        data_text = json.loads(data_json)

        # Store data in global variables.
        for line in data_text["objectives"]:
            objectives[line] = False
        for word in data_text["starting location"]:
            start_location = word.strip()
        for location in data_text["locations"]:
            locations.append(location)

    return start_location

def main():

    # Get the file from the user and use it to set up to program.
    load_file = input("Select a level file to run: ")
    start_location = setup(load_file)
    global current_scene
    current_scene = start_location

    # As long as the task has not been finished, keep loading the different scenes.
    while current_scene != "End":
        os.system('CLS')
        current_scene = load_scene(current_scene, load_file)

    # When you complete the task, get victory sequence.
    print("You win!")

def load_scene(current_scene, filename):

    # Make a empty list for later use with correct options.
    options = []

    with open(filename) as level_data:

        # Make data readable by python.
        data_json = level_data.read()
        data_text = json.loads(data_json)

        # Break down the nested data.
        locations = data_text["locations"]
        location_data = locations[current_scene]

        # Print out scene information for user and give options.
        for key in location_data.keys():
            if key == "Storyline":
                print(f"\n{current_scene} Data:")
                print(*location_data[key])
                print()
            elif key != "Type":
                print(key)
                options.append(key)
        
        # After collecting items from the file, make the move option available.
        print("Move")
        options.append("Move")

        # Get user input.
        user_decision = input(f"Please select an option: ")

        # Make sure the input is a correct one.
        valid_option_found = False
        for option in options:
            if user_decision == option:
                valid_option_found = True
        
        # If the user-choice matches an option, process it.
        if valid_option_found == True:
            if user_decision.capitalize() == "Move":
                current_scene = move(current_scene)
            else:
                current_scene = interact(filename, current_scene, user_decision)
        
        # If the user-choice does not match any available options, keep it from crashing the program.
        else:
            print("That is not a valid entry. Please try again.\n")
            input("Press ENTER to continue")

    return current_scene

def move(current_scene):
    
    # List out the available locations.
    print()
    print("Locations:")
    for location in locations:
        if location != current_scene:
            print(location)
    
    # Get the user's choice.
    move_decision = input("\nWhere would you like to go? ")
    current_scene = move_decision.capitalize()
    print()
    
    return current_scene

def interact(filename, current_scene, user_decision):
    with open(filename) as level_data:

        # Make data readable by python.
        data_json = level_data.read()
        data_text = json.loads(data_json)

        # Break down the nested data.
        locations = data_text["locations"]
        location_data = locations[current_scene]
        location_type = location_data["Type"]

    # Pinpoint the person or object being interacted with.
    interact_target = location_data[user_decision]

    # Sort locations by their type for ease of computation.
    # If the location is unlock, they just get the item.
    if location_type == ["Unlock"]:
        print(interact_target[0])
        objectives[interact_target[1]] = True

    # If the location is lock/unlock, they both need an object and get one.
    elif location_type == ["Lock/Unlock"]:

        # If the needed object has been obtained:
        if objectives[interact_target[0]] == True:
            print(interact_target[1])
            if len(interact_target) == 4:
                unlocked_objective = interact_target[3]
                objectives[unlocked_objective] = True

        # Otherwise:
        else:
            print(interact_target[2])
    
    # Lastly, if the location type is lock, it is the end of the game.
    elif location_type == ["Lock"]:

        # If the object has been obtained:
        if objectives[interact_target[0]] == True:
            print(interact_target[1])
            current_scene = "End"
        
        # Otherwise:
        else:
            print(interact_target[2])
    
    print()


    input("Press ENTER to continue")
    return current_scene

main()