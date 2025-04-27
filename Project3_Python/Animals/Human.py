from Organism import OrganismsEnum, Point
from Animal import Animal
from enum import Enum


class Human(Animal):
    __DEFAULT_INITIATIVE = 4
    __NUMBER_OF_TURNS_WITH_ABILITY_ON = 5

    class Move(Enum):
        NOMOVE = 0
        LEFT = 1
        RIGHT = 2
        UP = 3
        DOWN = 4

    def __init__(self, world, position, strength=None, def_strength=5, is_ability_on=False, n_until_activation=0):
        super().__init__(world, position)
        self.type_of_organism = OrganismsEnum.Human
        self._initiative = Human.__DEFAULT_INITIATIVE
        self.DEFAULT_STRENGTH = def_strength
        if strength is not None:
            self.strength = strength
        else:
            self.strength = self.DEFAULT_STRENGTH
        self.is_ability_on = is_ability_on
        self.number_of_rounds_until_possible_activation = n_until_activation

        self.current_move = Human.Move.NOMOVE

    def special_ability(self):
        if self.number_of_rounds_until_possible_activation == 0 and not self.is_ability_on:
            self.DEFAULT_STRENGTH = self.strength
            self.strength += Human.__NUMBER_OF_TURNS_WITH_ABILITY_ON
            self.is_ability_on = True
            message = "Special Ability Activated. Current strength: " + str(self.strength) + \
                      ".\nWill decrease until strength is back to normal."
        elif self.number_of_rounds_until_possible_activation != 0:
            message = "Cannot activate Special Ability.\nWill be possible in: " + \
                      str(self.number_of_rounds_until_possible_activation) + " turns."
        else:
            message = "Ability is already on. Current strength: " + str(self.strength) + "."
        return message

    def decrease_ability(self):
        if self.is_ability_on:
            self.strength -= 1
            if self.strength <= self.DEFAULT_STRENGTH:
                self.number_of_rounds_until_possible_activation = 5
                self.is_ability_on = False

    def decrease_ability_counter(self):
        if self.number_of_rounds_until_possible_activation != 0:
            self.number_of_rounds_until_possible_activation -= 1

    def handle_special_ability(self):
        self.decrease_ability()
        self.decrease_ability_counter()

    def change_move(self, new_move):
        self.current_move = new_move

    def get_new_human_position(self):
        if self.current_move == Human.Move.LEFT and self._position.x >= self._step:
            new_position = Point(self._position.x - self._step, self._position.y)
        elif self.current_move == Human.Move.RIGHT and self._position.x < self._world.get_size_of_world().x - self._step:
            new_position = Point(self._position.x + self._step, self._position.y)
        elif self.current_move == Human.Move.UP and self._position.y >= self._step:
            new_position = Point(self._position.x, self._position.y - self._step)
        elif self.current_move == Human.Move.DOWN and self._position.y < self._world.get_size_of_world().y - self._step:
            new_position = Point(self._position.x, self._position.y + self._step)
        else:
            return Point(-1, -1)
        return new_position

    def action(self):
        new_position = self.get_new_human_position()
        if new_position.x == -1:
            return False
        self._prev_position = self._position
        self._position = new_position
        self.try_to_go_to_position()
        return True

    def __str__(self):
        return "Human"

    def save_organism(self):
        return str(self.type_of_organism.value) + " " + str(self._position.x) + " " + str(self._position.y) + " " + \
               str(self._prev_position.x) + " " + str(self._prev_position.y) + " " + str(self.strength) + " " + \
               str(self.DEFAULT_STRENGTH) + " " + str(self.is_ability_on) + " " + \
               str(self.number_of_rounds_until_possible_activation) + "\n"
