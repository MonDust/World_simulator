import World
from Plant import Plant
from Organism import OrganismsEnum


class Guarana(Plant):
    def __init__(self, world, position):
        super().__init__(world, position)
        self.type_of_organism = OrganismsEnum.Guarana

    def collision(self, attacker_organism):
        attacker_organism.put_into_world()
        if self.strength > attacker_organism.get_strength():
            self.put_into_world()
            if attacker_organism.get_type_of_organism() == OrganismsEnum.Human:
                self._world.delete_human()
                return
            self._world.remove_organism_from_list(attacker_organism)
            self._world.add_comment(str(attacker_organism) + " ate " + str(self) + " and died.")
        else:
            self._world.remove_organism_from_list(self)
            attacker_organism.increase_strength(3)
            self._world.add_comment(str(attacker_organism) + " ate " + str(self) + " and got stronger.")

    def __str__(self):
        return "Guarana"
