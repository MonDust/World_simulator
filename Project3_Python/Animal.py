import World
import random
from Organism import Organism, OrganismsEnum


class Animal(Organism):
    THE_FLOOR_OF_ESCAPE_ANTELOPE = 50

    def __init__(self, world, position, strength=0):
        super().__init__(world, position, strength)

    def action(self):
        new_position = self.get_new_position()
        if new_position.x == -1:
            return False
        self._prev_position = self._position
        self._position = new_position
        self.try_to_go_to_position()
        return True

    def multiply_organism(self):
        new_position = self.get_new_position()
        if new_position.x != -1:
            if self._world.check_if_not_occupied(new_position):
                self._world.add_organism(self.type_of_organism, new_position)
                self._world.add_comment(str(self) + " multiplied.")

    def collision(self, attacker_organism):
        probability_of_escape = random.randint(0, 100)
        attacker_organism.put_into_world()

        if self.type_of_organism == attacker_organism.type_of_organism:
            self.multiply_organism()
            return

        if probability_of_escape < self.THE_FLOOR_OF_ESCAPE_ANTELOPE:
            new_position = self.get_new_position()
            if new_position.x != -1 and self._world.check_if_not_occupied(new_position):
                if attacker_organism.type_of_organism == OrganismsEnum.Antelope:
                    attacker_organism.change_position(new_position)
                    attacker_organism.put_into_world()
                    self.put_into_world()
                    self._world.add_comment(str(attacker_organism) + " escaped.")
                    return
                elif self.type_of_organism == OrganismsEnum.Antelope:
                    self.change_position(new_position)
                    self.put_into_world()
                    self._world.add_comment(str(self) + " escaped.")
                    return

        if self.strength > attacker_organism.strength:
            self.put_into_world()
            if attacker_organism.type_of_organism != OrganismsEnum.Human:
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
