from Animal import Animal

from Organism import OrganismsEnum


class Wolf(Animal):
    __DEFAULT_INITIATIVE = 5
    __DEFAULT_STRENGTH = 9

    def __init__(self, world, position, strength=__DEFAULT_STRENGTH):
        super().__init__(world, position, strength)
        self.type_of_organism = OrganismsEnum.Wolf
        self._initiative = self.__DEFAULT_INITIATIVE

    def __str__(self):
        return "Wolf"
