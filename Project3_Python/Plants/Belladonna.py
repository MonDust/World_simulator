import World
from Dangerous_Plant import Dangerous_Plant
from Organism import OrganismsEnum


class Belladonna(Dangerous_Plant):
    __DEFAULT_STRENGTH = 99

    def __init__(self, world, position):
        super().__init__(world, position)
        self.type_of_organism = OrganismsEnum.Belladonna
        self.strength = Belladonna.__DEFAULT_STRENGTH

    def __str__(self):
        return "Belladonna"
