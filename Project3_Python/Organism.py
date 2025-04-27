import random
from enum import Enum


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


class OrganismsEnum(Enum):
    Wolf = 1
    Fox = 2
    Turtle = 3
    Antelope = 4
    Sheep = 5
    Belladonna = 6
    Grass = 7
    Guarana = 8
    Hogweed = 9
    Sow_thistle = 10
    Cyber_Sheep = 11
    Human = 12
    Default_organism = 13


class Organism:
    _world = None
    number_of_organism = 10

    def __init__(self, world, position, strength=0):
        self._world = world
        self._position = position
        self._prev_position = Point(-1, -1)
        self.strength = strength
        self._initiative = 0
        self._step = 1
        self.type_of_organism = OrganismsEnum.Default_organism
        self._is_animal = True

    def get_initiative(self):
        return self._initiative

    def get_strength(self):
        return self.strength

    def get_prev_position(self):
        return self._prev_position

    def get_position(self):
        return self._position

    def exchange_positions(self):
        tmp = Point(self._position.x, self._position.y)
        self._position = self._prev_position
        self._prev_position = tmp

    def change_position(self, new_position):
        self._prev_position = self._position
        self._position = new_position

    def is_equal_in_the_prev_position(self):
        return self._world.is_equal_in_the_position(self, self._prev_position)

    def put_into_world(self):
        if self.is_equal_in_the_prev_position():
            self._world.null_the_position(self._prev_position)
        self._world.put_established_organism_to_world(self)

    def is_organism_an_animal(self):
        return self._is_animal

    def get_type_of_organism(self):
        return self.type_of_organism

    def increase_strength(self, increase=1):
        self.strength += increase

    def decrease_strength(self):
        self.strength -= 1

    def get_new_position(self):
        number_of_possible_positions = 4
        move = random.randint(0, number_of_possible_positions - 1)

        if move == 0 and self._position.x >= self._step:  # Direction Left
            new_position = Point(self._position.x - self._step, self._position.y)
        elif move == 1 and self._position.x < self._world.get_size_of_world().x - self._step:  # Direction Right
            new_position = Point(self._position.x + self._step, self._position.y)
        elif move == 2 and self._position.y >= self._step:  # Direction Up
            new_position = Point(self._position.x, self._position.y - self._step)
        elif move == 3 and self._position.y < self._world.get_size_of_world().y - self._step:  # Direction Down
            new_position = Point(self._position.x, self._position.y + self._step)
        else:
            return Point(-1, -1)

        return new_position

    def save_organism(self):
        return (
                str(self.type_of_organism.value)
                + " "
                + str(self._position.x)
                + " "
                + str(self._position.y)
                + " "
                + str(self._prev_position.x)
                + " "
                + str(self._prev_position.y)
                + " "
                + str(self.strength)
                + "\n"
        )

    @staticmethod
    def get_organism(organism_type, world, position, strength=None):
        from Plants import Belladonna, Grass, Guarana, Hogweed, Sow_Thistle
        from Animals import Antelope, Cyber_Sheep, Fox, Sheep, Turtle, Wolf
        new_organism = None
        if organism_type is None:
            exclude_list = [OrganismsEnum.Human, OrganismsEnum.Default_organism]
            filtered_list = [organism for organism in OrganismsEnum if organism not in exclude_list]
            organism_type = random.choice(filtered_list)

        if strength is None:
            if organism_type == OrganismsEnum.Wolf:
                new_organism = Wolf(world, position)
            elif organism_type == OrganismsEnum.Fox:
                new_organism = Fox(world, position)
            elif organism_type == OrganismsEnum.Sheep:
                new_organism = Sheep(world, position)
            elif organism_type == OrganismsEnum.Antelope:
                new_organism = Antelope(world, position)
            elif organism_type == OrganismsEnum.Turtle:
                new_organism = Turtle(world, position)
            elif organism_type == OrganismsEnum.Belladonna:
                new_organism = Belladonna(world, position)
            elif organism_type == OrganismsEnum.Grass:
                new_organism = Grass(world, position)
            elif organism_type == OrganismsEnum.Sow_thistle:
                new_organism = Sow_Thistle(world, position)
            elif organism_type == OrganismsEnum.Guarana:
                new_organism = Guarana(world, position)
            elif organism_type == OrganismsEnum.Hogweed:
                new_organism = Hogweed(world, position)
            elif organism_type == OrganismsEnum.Cyber_Sheep:
                new_organism = Cyber_Sheep(world, position)
        else:
            if organism_type == OrganismsEnum.Wolf:
                new_organism = Wolf(world, position, strength)
            elif organism_type == OrganismsEnum.Fox:
                new_organism = Fox(world, position, strength)
            elif organism_type == OrganismsEnum.Sheep:
                new_organism = Sheep(world, position, strength)
            elif organism_type == OrganismsEnum.Antelope:
                new_organism = Antelope(world, position, strength)
            elif organism_type == OrganismsEnum.Turtle:
                new_organism = Turtle(world, position, strength)
            elif organism_type == OrganismsEnum.Belladonna:
                new_organism = Belladonna(world, position)
            elif organism_type == OrganismsEnum.Grass:
                new_organism = Grass(world, position)
            elif organism_type == OrganismsEnum.Sow_thistle:
                new_organism = Sow_Thistle(world, position)
            elif organism_type == OrganismsEnum.Guarana:
                new_organism = Guarana(world, position)
            elif organism_type == OrganismsEnum.Hogweed:
                new_organism = Hogweed(world, position)
            elif organism_type == OrganismsEnum.Cyber_Sheep:
                new_organism = Cyber_Sheep(world, position, strength)

        return new_organism

    def try_to_go_to_position(self):
        if self._world.check_if_not_occupied(self._position):
            self.put_into_world()
        else:
            self._world.get_organism_in_position(self._position).collision(self)

    def action(self):
        pass

    def collision(self, attacker_organism):
        attacker_organism.put_into_world()

        if self.strength > attacker_organism.strength:
            self.put_into_world()

            if attacker_organism.get_type_of_organism() == OrganismsEnum.Human:
                self._world.delete_human()

            self._world.remove_organism_from_list(attacker_organism)
            self._world.add_comment(str(self) + " won with " + str(attacker_organism))
        else:
            self._world.remove_organism_from_list(self)
            self._world.add_comment(str(attacker_organism) + " won with " + str(self))

    def __str__(self):
        return "Ground"

    def get_image(self):
        return str(self) + ".jpg"
