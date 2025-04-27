from Animal import Animal
from Organism import OrganismsEnum


class Antelope(Animal):
    __DEFAULT_INITIATIVE = 4
    __DEFAULT_STRENGTH = 4
    __DEFAULT_STEPS = 2

    def __init__(self, world, position, strength=__DEFAULT_STRENGTH):
        super().__init__(world, position, strength)
        self.type_of_organism = OrganismsEnum.Antelope
        self._initiative = Antelope.__DEFAULT_INITIATIVE
        self._step = Antelope.__DEFAULT_STEPS

    def __str__(self):
        return "Antelope"
