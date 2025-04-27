import Organism
from Organism import OrganismsEnum, Point
import random
from Animals import Human


class World:
    PERCENT_OF_THE_WORLD = 0.1

    def __init__(self, size_of_the_world):
        self._list_of_organisms = []
        self._commentator = []
        self._a_big_warrior = None
        self._map_of_organisms = [[None] * size_of_the_world.y for _ in range(size_of_the_world.x)]
        self.__number_of_organisms = 0
        self.__size_of_world = size_of_the_world
        self.__turn = 1
        self.__number_of_animals = 0
        self.__initialize_organisms()
        # print(len(self.list_of_organisms))
        # self.print_map()

    def __is_human_alive(self):
        return self._a_big_warrior is not None

    def special_ability_on(self):
        if self._a_big_warrior:
            return self._a_big_warrior.special_ability()
        return "Human died."

    def get_all_organisms_by_type(self, organism_type = OrganismsEnum.Hogweed):
        t_organism_list = []
        for i in range(len(self._list_of_organisms)):
            if self._list_of_organisms[i].get_type_of_organism() == organism_type:
                t_organism_list.append(self._list_of_organisms[i])
        return t_organism_list

    @staticmethod
    def __sort_organisms_by_initiative(organisms):
        organisms.sort(key=lambda o: o.get_initiative(), reverse=True)

    def clear_world(self):
        for i in range(self.__size_of_world.x):
            for j in range(self.__size_of_world.y):
                self._map_of_organisms[i][j] = None

    def delete_world(self):
        self._commentator.clear()
        self._list_of_organisms.clear()
        self.clear_world()
        self.__number_of_organisms = 0
        self._a_big_warrior = None
        self.__turn = 1

    def __initialize_all_organisms(self):
        self.clear_world()
        if self._list_of_organisms:
            for organism in self._list_of_organisms:
                org_position = organism.get_position()
                self._map_of_organisms[org_position.x][org_position.y] = organism
        if self._a_big_warrior:
            warrior_position = self._a_big_warrior.get_position()
            self._map_of_organisms[warrior_position.x][warrior_position.y] = self._a_big_warrior

    def add_comment(self, message):
        self._commentator.append(message)

    def print_comments(self):
        if not self._commentator:
            print("Nothing happened.")
        else:
            for comment in self._commentator:
                print(comment)

    def make_save_file_contents(self):
        save_file_list = []
        if self._a_big_warrior:
            save_file_list.append(self._a_big_warrior.save_organism())
        if self._list_of_organisms:
            for organism in self._list_of_organisms:
                save_file_list.append(organism.save_organism())
        return save_file_list

    def _clear_comments(self):
        self._commentator.clear()

    def get_commentator(self):
        return self._commentator

    def make_turn(self, human_move):
        self._clear_comments()
        print("Turn:", self.__turn)
        self.__sort_organisms_by_initiative(self._list_of_organisms)
        human_flag = True
        self.__number_of_organisms = len(self._list_of_organisms)
        for i in range(self.__number_of_organisms):
            if i >= self.__number_of_organisms:
                break
            organism = self._list_of_organisms[i]
            if self._a_big_warrior:
                if organism.get_initiative() < self._a_big_warrior.get_initiative() and human_flag:
                    self._a_big_warrior.change_move(human_move)
                    self._a_big_warrior.action()
                    human_flag = False
            organism.action()
        if self._a_big_warrior:
            self._a_big_warrior.handle_special_ability()
        self.__turn += 1
        self.__initialize_all_organisms()
        # self.print_map()

    def remove_organism_from_list(self, organism_to_remove):
        self._list_of_organisms.remove(organism_to_remove)
        self.__number_of_organisms -= 1

    def get_size_of_world(self):
        return self.__size_of_world

    def get_organism_in_position(self, the_position):
        return self._map_of_organisms[the_position.x][the_position.y]

    def is_equal_in_the_position(self, the_organism, the_position):
        if the_position.x == -1:
            return False
        if self._map_of_organisms[the_position.x][the_position.y] is None:
            return False
        return self._map_of_organisms[the_position.x][the_position.y] == the_organism

    def null_the_position(self, the_position):
        self._map_of_organisms[the_position.x][the_position.y] = None

    def put_established_organism_to_world(self, the_organism):
        the_position = the_organism.get_position()
        self._map_of_organisms[the_position.x][the_position.y] = the_organism

    def check_if_not_occupied(self, the_position):
        return self._map_of_organisms[the_position.x][the_position.y] is None

    @staticmethod
    def _get_random_organism():
        return OrganismsEnum.values()[random.randint(0, len(OrganismsEnum.values()) - 1)]

    def _get_random_position(self):
        value_x = random.randint(0, self.__size_of_world.x - 1)
        value_y = random.randint(0, self.__size_of_world.y - 1)
        return Point(value_x, value_y)

    def __add_one_instance_of_all(self):
        for organism_enum in list(OrganismsEnum):
            self.add_organism(organism_enum)

    def add_organism(self, organism_type=None, position=None, strength=None):
        if position is None:
            position = self._get_random_position()
            try_ten_times = 10
            i = 0
            while self._map_of_organisms[position.x][position.y] is not None:
                if i == try_ten_times:
                    return
                position = self._get_random_position()
                i += 1
        if strength is None:
            new_organism = Organism.Organism.get_organism(organism_type, self, position)
        else:
            new_organism = Organism.Organism.get_organism(organism_type, self, position, strength)
        if new_organism is not None:
            self._list_of_organisms.append(new_organism)
            self._map_of_organisms[position.x][position.y] = new_organism

    def delete_human(self):
        self._a_big_warrior = None

    def add_human(self, position=None, strength=5, def_strength=5, is_ability_on=False, n_until_activation=0):
        if position is None:
            position = self._get_random_position()
            self._a_big_warrior = Human(self, position)
        else:
            self._a_big_warrior = Human(self, position, strength, def_strength, is_ability_on, n_until_activation)
        if self._a_big_warrior is not None:
            self._map_of_organisms[position.x][position.y] = self._a_big_warrior

    def __initialize_organisms(self):
        max_size = self.__size_of_world.x * self.__size_of_world.y - 1
        self.__number_of_animals = int(max_size * self.PERCENT_OF_THE_WORLD)
        self.add_human()
        self.__add_one_instance_of_all()
        for i in range(self.__number_of_animals):
            self.add_organism()
        #print(self.__number_of_animals)

    def print_map(self):
        for i in range(self.__size_of_world.x):
            for j in range(self.__size_of_world.y):
                print(self._map_of_organisms[i][j], end=' ')
            print()
