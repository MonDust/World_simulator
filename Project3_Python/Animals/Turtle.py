from Animal import Animal

import random
from Organism import OrganismsEnum


class Turtle(Animal):
    __DEFAULT_INITIATIVE = 1
    __DEFAULT_STRENGTH = 2
    __TURTLE_DEFENSE = 5
    __THE_FLOOR_OF_TURTLE_MOVEMENT = 75

    def __init__(self, world, position, strength=__DEFAULT_STRENGTH):
        super().__init__(world, position, strength)
        self.type_of_organism = OrganismsEnum.Turtle
        self._initiative = self.__DEFAULT_INITIATIVE

    def collision(self, attacker_organism):
        probability_of_escape = random.randint(0, 99)
        attacker_organism.put_into_world()

        if self.type_of_organism == attacker_organism.get_type_of_organism():
            self.multiply_organism()
            return

        if probability_of_escape < self.THE_FLOOR_OF_ESCAPE_ANTELOPE:
            new_position = self.get_new_position()
            if new_position.x != -1 and self._world.check_if_not_occupied(new_position):
                if attacker_organism.get_type_of_organism() == OrganismsEnum.Antelope:
                    attacker_organism.change_position(new_position)
                    attacker_organism.put_into_world()
                    self.put_into_world()
                    self._world.add_comment(str(attacker_organism) + " escaped.")
                    return

        if self.__TURTLE_DEFENSE > attacker_organism.get_strength():
            attacker_organism.exchange_positions()
            attacker_organism.put_into_world()
            self.put_into_world()
            self._world.add_comment(str(self) + " deflected the attack.")

        if self.strength > attacker_organism.get_strength():
            self.put_into_world()
            if attacker_organism.get_type_of_organism() != OrganismsEnum.Human:
                self._world.remove_organism_from_list(attacker_organism)
            else:
                self._world.delete_human()
            self._world.add_comment(str(self) + " won with " + str(attacker_organism))
        else:
            if self.type_of_organism != OrganismsEnum.Human:
                self._world.remove_organism_from_list(self)
            else:
                self._world.delete_human()
            self._world.add_comment(str(attacker_organism) + " won with " + str(self))

    def action(self):
        new_position = self.get_new_position()
        possibility_of_movement = random.randint(0, 99)
        if new_position.x == -1 or possibility_of_movement < self.__THE_FLOOR_OF_TURTLE_MOVEMENT:
            return False
        self._prev_position = self._position
        self._position = new_position
        self.try_to_go_to_position()
        return True

    def __str__(self):
        return "Turtle"
