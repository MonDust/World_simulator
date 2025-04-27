import tkinter as tk
from PIL import ImageTk, Image
import os
from Organism import Point, OrganismsEnum
from Animals.Human import Human
from Saving_and_loading import SaveAndLoad


class Visuals:
    def __init__(self, world):
        self.__world = world
        self.__size_of_world = world.get_size_of_world()
        self.__image_folder = os.path.join(os.path.dirname(__file__), "Images")
        self.__panel_size = max(1, min(500 // self.__size_of_world.y, 500 // self.__size_of_world.x))
        self.__size_of_screen = Point((self.__panel_size + 2) * self.__size_of_world.y,
                                      (self.__panel_size + 2) * self.__size_of_world.x)
        self.__image_panels = []

        self.__window = tk.Tk()
        self.__window.title("World")

        self.__create_image_grid()
        self.__create_buttons()
        self.__window.bind("<Up>", lambda event: self.__move(Human.Move.LEFT))
        self.__window.bind("<Down>", lambda event: self.__move(Human.Move.RIGHT))
        self.__window.bind("<Left>", lambda event: self.__move(Human.Move.UP))
        self.__window.bind("<Right>", lambda event: self.__move(Human.Move.DOWN))
        self.__Save_and_Load = SaveAndLoad(self.__world)

    def __create_buttons(self):
        button_frame = tk.Frame(self.__window)
        button_frame.grid(row=self.__size_of_world.x, columnspan=self.__size_of_world.y, padx=10, pady=10)

        status_button = tk.Button(button_frame, text="Status", command=self.__show_status)
        status_button.grid(row=0, column=0, padx=5)

        next_turn_button = tk.Button(button_frame, text="Next Turn", command=self.__next_turn)
        next_turn_button.grid(row=0, column=1, padx=5)

        special_ability_button = tk.Button(button_frame, text="Special Ability", command=self.__special_ability)
        special_ability_button.grid(row=0, column=2, padx=5)

        save_button = tk.Button(button_frame, text="Save", command=self.__save)
        save_button.grid(row=0, column=3, padx=5)

        load_button = tk.Button(button_frame, text="Load", command=self.__load)
        load_button.grid(row=0, column=4, padx=5)

    def __show_status(self):
        self.__world.print_comments()

    def __next_turn(self):
        self.__world.make_turn(Human.Move.NOMOVE)
        self.__update_all_image()

    @staticmethod
    def __show_popup_message(message):
        popup_window = tk.Toplevel()
        popup_window.title("Popup")
        label = tk.Label(popup_window, text=message)
        label.pack(padx=20, pady=20)
        popup_window.mainloop()

    def __special_ability(self):
        message = self.__world.special_ability_on()
        self.__show_popup_message(message)

    def __save(self):
        self.__Save_and_Load.make_save_file()

    def __load(self):
        self.__Save_and_Load.load_organisms()
        self.__update_all_image()

    def __move(self, direction):
        self.__world.make_turn(direction)
        self.__update_all_image()

    def __image_clicked(self, row, col):
        if not self.__world.check_if_not_occupied(Point(row, col)):
            return

        def change_image(r, c, org_type):
            if org_type != OrganismsEnum.Human and org_type != OrganismsEnum.Default_organism:
                self.__world.add_organism(org_type, Point(r, c))
                self.__update_image(r, c)  # here image changes to be microscopic

        menu = tk.Menu(self.__window, tearoff=0)
        for organism_type in OrganismsEnum:
            if organism_type != OrganismsEnum.Human and organism_type != OrganismsEnum.Default_organism:
                menu.add_command(label=organism_type.name,
                                 command=lambda r=row, c=col, ot=organism_type: change_image(r, c, ot))

        x = self.__image_panels[row * self.__size_of_world.y + col].winfo_rootx() + self.__panel_size // 2
        y = self.__image_panels[row * self.__size_of_world.y + col].winfo_rooty() + self.__panel_size // 2
        menu.post(x, y)

    def __create_image_panel(self, row, col):
        panel = tk.Label(self.__window, bd=1, relief="solid", width=self.__panel_size, height=self.__panel_size)
        panel.grid(row=row, column=col, padx=0, pady=0)
        panel.bind("<Button-1>", lambda event, r=row, c=col: self.__image_clicked(r, c))

        panel.grid_rowconfigure(0, weight=1)
        panel.grid_columnconfigure(0, weight=1)

        self.__image_panels.append(panel)
        self.__update_image(row, col)

    def __update_image(self, row, col):
        organism = self.__world.get_organism_in_position(Point(row, col))
        if organism is not None:
            image_path = os.path.join(self.__image_folder, f"{organism}.jpg")
        else:
            image_path = os.path.join(self.__image_folder, "Ground.jpg")

        image = Image.open(image_path)
        image = image.resize((self.__panel_size, self.__panel_size))
        image = ImageTk.PhotoImage(image)
        self.__image_panels[row * self.__size_of_world.y + col].config(image=image)
        self.__image_panels[row * self.__size_of_world.y + col].image = image

    def __update_all_image(self):
        for row in range(self.__size_of_world.x):
            for col in range(self.__size_of_world.y):
                self.__update_image(row, col)

    def __create_image_grid(self):
        for row in range(self.__size_of_world.x):
            for col in range(self.__size_of_world.y):
                self.__create_image_panel(row, col)

    def main(self):
        self.__window.mainloop()
