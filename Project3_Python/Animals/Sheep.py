from Animal import Animal

from Organism import OrganismsEnum


class Sheep(Animal):
    __DEFAULT_INITIATIVE = 4
    __DEFAULT_STRENGTH = 4

    def __init__(self, world, position, strength=__DEFAULT_STRENGTH):
        super().__init__(world, position, strength)
        self.type_of_organism = OrganismsEnum.Sheep
        self._initiative = self.__DEFAULT_INITIATIVE

    def __str__(self):
        return "Sheep"
