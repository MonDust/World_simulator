from Organism import Organism

import random


class Plant(Organism):
    __THE_FLOOR_OF_SPREAD = 10

    def __init__(self, world, position, strength=0):
        super().__init__(world, position, strength)
        self._is_animal = False

    def action(self):
        probability_of_spread = random.randint(0, 100)

        if probability_of_spread < self.__THE_FLOOR_OF_SPREAD:
            new_position = self.get_new_position()
            if new_position.x == -1:
                return False
            if self._world.check_if_not_occupied(new_position):
                self._world.add_organism(self.type_of_organism, new_position)
                self._world.add_comment(str(self) + " spread.")
                return True

        return False

    def get_image(self):
        file_name = "Images/" + str(self) + ".jpg"
        return file_name
