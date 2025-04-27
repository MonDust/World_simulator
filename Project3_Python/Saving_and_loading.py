import os
from tkinter import messagebox, filedialog
from tkinter.filedialog import asksaveasfilename
from Organism import OrganismsEnum, Point


class SaveAndLoad:
    def __init__(self, world):
        self.__world = world

    def load_organisms(self):

        try:
            file_path = filedialog.askopenfilename(title="Select Save File", filetypes=(("Text Files", "*.txt"),))
            if file_path:
                with open(file_path, "r") as file:
                    lines = file.readlines()
                    self.__world.delete_world()
                    for line in lines:
                        line_split = line.split()
                        organism_type = OrganismsEnum(int(line_split[0]))
                        if organism_type:
                            position = Point(int(line_split[1]), int(line_split[2]))
                            strength = int(line_split[5])
                            if organism_type == OrganismsEnum.Human:
                                def_strength = int(line_split[6])
                                is_ability = bool(line_split[7])
                                n_until_activation = int(line_split[8])
                                self.__world.add_human(position, strength, def_strength, is_ability, n_until_activation)
                            else:
                                self.__world.add_organism(organism_type, position, strength)
                        else:
                            print(f"Invalid organism type: {line_split[0]}")
                messagebox.showinfo("Load File", "File loaded successfully.")
        except IOError as e:
            messagebox.showerror("Error", f"Error reading the file: {e}")

    def make_save_file(self):
        file_name = asksaveasfilename(title="Save File", filetypes=(("Text Files", "*.txt"),))

        if file_name:
            contents = self.__world.make_save_file_contents()

            save_files_dir = os.path.join(os.getcwd(), "SaveFiles")
            if not os.path.exists(save_files_dir):
                os.makedirs(save_files_dir)

            new_file = os.path.join(save_files_dir, file_name + ".txt")
            try:
                with open(new_file, "w") as file:
                    file.writelines(contents)

                messagebox.showinfo("Save File", "File saved successfully.")
            except IOError:
                messagebox.showerror("Save File", "Error occurred while saving the file.")
