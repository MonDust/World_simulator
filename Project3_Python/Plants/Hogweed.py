import World
from Dangerous_Plant import Dangerous_Plant
from Organism import OrganismsEnum, Point


class Hogweed(Dangerous_Plant):
    __DEFAULT_STRENGTH = 10

    def __init__(self, world, position):
        super().__init__(world, position)
        self.type_of_organism = OrganismsEnum.Hogweed
        self.strength = Hogweed.__DEFAULT_STRENGTH

    def __str__(self):
        return "Hogweed"

    def kill_in_position(self, position_to_kill):
        if not self._world.check_if_not_occupied(position_to_kill):
            if self._world.get_organism_in_position(position_to_kill).type_of_organism != OrganismsEnum.Cyber_Sheep:
                if self._world.get_organism_in_position(position_to_kill).is_organism_an_animal():
                    self._world.add_comment(str(self) + " killed " + str(self._world.get_organism_in_position(position_to_kill)))
                    if self._world.get_organism_in_position(position_to_kill).get_type_of_organism() == OrganismsEnum.Human:
                        self._world.delete_human()
                    else:
                        self._world.remove_organism_from_list(self._world.get_organism_in_position(position_to_kill))
                    self._world.null_the_position(position_to_kill)

    def kill_around(self):
        world_size = self._world.get_size_of_world()
        step = 1
        if self._position.x < world_size.x - step:
            checked_position = Point(self._position.x + step, self._position.y)
            self.kill_in_position(checked_position)
        if self._position.x >= step:
            checked_position = Point(self._position.x - step, self._position.y)
            self.kill_in_position(checked_position)
        if self._position.y < world_size.y - step:
            checked_position = Point(self._position.x, self._position.y + step)
            self.kill_in_position(checked_position)
        if self._position.y >= step:
            checked_position = Point(self._position.x, self._position.y - step)
            self.kill_in_position(checked_position)

    def action(self):
        flag = super().action()
        self.kill_around()
        return flag
