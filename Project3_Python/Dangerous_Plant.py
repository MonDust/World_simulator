import World
from Plant import Plant
from Organism import OrganismsEnum


class Dangerous_Plant(Plant):
    def __init__(self, world, position):
        super().__init__(world, position)

    def collision(self, attacker_organism):
        attacker_organism.put_into_world()
        if self.type_of_organism == OrganismsEnum.Hogweed and attacker_organism.type_of_organism == OrganismsEnum.Cyber_Sheep:
            if self.strength <= attacker_organism.strength:
                self._world.remove_organism_from_list(self)
                self._world.add_comment(str(attacker_organism) + " won with " + str(self))
                return
        self._world.null_the_position(self._position)
        if attacker_organism.get_type_of_organism() == OrganismsEnum.Human:
            self._world.delete_human()
            self._world.remove_organism_from_list(self)
            return
        self._world.remove_organism_from_list(attacker_organism)
        self._world.remove_organism_from_list(self)
        self._world.add_comment(str(attacker_organism) + " ate " + str(self) + " and died.")
