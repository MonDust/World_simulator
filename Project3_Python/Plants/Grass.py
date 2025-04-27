import World
from Plant import Plant
from Organism import OrganismsEnum


class Grass(Plant):
    def __init__(self, world, position):
        super().__init__(world, position)
        self.type_of_organism = OrganismsEnum.Grass

    def __str__(self):
        return "Grass"
