import World
from Plant import Plant
from Organism import OrganismsEnum


class Sow_Thistle(Plant):
    __TRY_TO_SPREAD = 3

    def __init__(self, world, position):
        super().__init__(world, position)
        self.type_of_organism = OrganismsEnum.Sow_thistle

    def action(self):
        flag = False
        for i in range(self.__TRY_TO_SPREAD):
            if flag:
                break
            flag = super().action()
        return flag

    def __str__(self):
        return "Sow_Thistle"
