from Organism import OrganismsEnum, Point
from Animal import Animal
import random


class Fox(Animal):
    __DEFAULT_INITIATIVE = 7
    __DEFAULT_STRENGTH = 3
    __moves = [0, 1, 2, 3]
    __number_of_possible_positions = 4

    def __init__(self, world, position, strength=__DEFAULT_STRENGTH):
        super().__init__(world, position, strength)
        self.type_of_organism = OrganismsEnum.Fox
        self._initiative = Fox.__DEFAULT_INITIATIVE

    def check_position_fox(self, cur_position, i_move):
        new_position = Point(-1, -1)
        if self._world.check_if_not_occupied(cur_position):
            new_position = cur_position
        else:
            if self.strength >= self._world.get_organism_in_position(cur_position).strength:
                new_position = cur_position
            else:
                self.__moves[i_move] = -1
                for i in range(i_move + 1, 4):
                    self.__moves[i] -= 1
                self.__number_of_possible_positions -= 1
        return new_position

    def get_new_fox_position(self):
        new_position = Point(-1, -1)
        random.seed()
        self.__number_of_possible_positions = 4
        for i in range(self.__number_of_possible_positions):
            self.__moves[i] = i

        while True:
            move = random.randint(0, self.__number_of_possible_positions - 1)
            if (
                    move == self.__moves[0]
                    and self._position.x >= self._step
            ):
                new_position = self.check_position_fox(
                    Point(self._position.x - self._step, self._position.y),
                    0
                )
            elif (
                    move == self.__moves[1]
                    and self._position.x < self._world.get_size_of_world().x - self._step
            ):
                new_position = self.check_position_fox(
                    Point(self._position.x + self._step, self._position.y),
                    1
                )
            elif (
                    move == self.__moves[2]
                    and self._position.y >= self._step
            ):
                new_position = self.check_position_fox(
                    Point(self._position.x, self._position.y - self._step),
                    2
                )
            elif (
                    move == self.__moves[3]
                    and self._position.y < self._world.get_size_of_world().y - self._step
            ):
                new_position = self.check_position_fox(
                    Point(self._position.x, self._position.y + self._step),
                    3
                )
            else:
                break

            if self.__number_of_possible_positions <= 0 or new_position.x != -1:
                break

        return new_position

    def action(self):
        new_position = self.get_new_fox_position()
        if new_position.x == -1:
            return False
        self._prev_position = self._position
        self._position = new_position
        self.try_to_go_to_position()
        return True

    def __str__(self):
        return "Fox"
