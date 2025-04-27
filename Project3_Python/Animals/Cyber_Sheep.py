from Animal import Animal
from Organism import OrganismsEnum, Point
import math
import random


def calculate_distance(pos1, pos2):
    return math.sqrt((pos1.x-pos2.x)**2 + (pos1.y-pos2.y)**2)


class Cyber_Sheep(Animal):
    __DEFAULT_INITIATIVE = 4
    __DEFAULT_STRENGTH = 11

    def __init__(self, world, position, strength=__DEFAULT_STRENGTH):
        super().__init__(world, position, strength)
        self.type_of_organism = OrganismsEnum.Cyber_Sheep
        self._initiative = self.__DEFAULT_INITIATIVE

    def action(self):
        new_position = self.move_towards_hogweed()
        if new_position.x == -2:
            new_position = self.get_new_position()
        if new_position.x == -1:
            return False
        self._prev_position = self._position
        self._position = new_position
        self.try_to_go_to_position()
        return True
        
    def move_towards_hogweed(self):
        hogweeds = self._world.get_all_organisms_by_type(OrganismsEnum.Hogweed)
        if len(hogweeds) == 0:
            return Point(-2, -2)
        if hogweeds:
            distances = [calculate_distance(hogweed.get_position(), self._position) for hogweed in hogweeds]
            min_distance = min(distances)
            closest_hogweeds = [hogweed for hogweed, distance in zip(hogweeds, distances) if distance == min_distance]
            target_hogweed = random.choice(closest_hogweeds)
            move = random.randint(0, 1)
            if move == 0:
                if target_hogweed.get_position().x < self._position.x and self._position.x >= self._step:
                    new_position = Point(self._position.x - self._step, self._position.y)  # Move Left
                elif target_hogweed.get_position().x > self._position.x and self._position.x < self._world.get_size_of_world().x - self._step:
                    new_position = Point(self._position.x + self._step, self._position.y)  # Move Right
                else:
                    if target_hogweed.get_position().y < self._position.y and self._position.y >= self._step:
                        new_position = Point(self._position.x, self._position.y - self._step)  # Move Up
                    elif target_hogweed.get_position().y > self._position.y and self._position.y < self._world.get_size_of_world().y - self._step:
                        new_position = Point(self._position.x, self._position.y + self._step)  # Move Down
                    else:
                        new_position = Point(-1, -1)
            else:
                if target_hogweed.get_position().y < self._position.y and self._position.y >= self._step:
                    new_position = Point(self._position.x, self._position.y - self._step)  # Move Up
                elif target_hogweed.get_position().y > self._position.y and self._position.y < self._world.get_size_of_world().y - self._step:
                    new_position = Point(self._position.x, self._position.y + self._step)  # Move Down
                else:
                    if target_hogweed.get_position().x < self._position.x and self._position.x >= self._step:
                        new_position = Point(self._position.x - self._step, self._position.y)  # Move Left
                    elif target_hogweed.get_position().x > self._position.x and self._position.x < self._world.get_size_of_world().x - self._step:
                        new_position = Point(self._position.x + self._step, self._position.y)  # Move Right
                    else:
                        new_position = Point(-1, -1)

            return new_position

    def __str__(self):
        return "Cyber_Sheep"
