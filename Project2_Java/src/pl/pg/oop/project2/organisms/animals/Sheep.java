package pl.pg.oop.project2.organisms.animals;

import pl.pg.oop.project2.organisms.Animal;
import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.World;

import java.awt.*;

public class Sheep extends Animal {
    private final static int DEFAULT_INITIATIVE = 4;
    private final static int DEFAULT_STRENGTH = 4;
    public Sheep(World world, Point position) {
        super(world, position);
        this.TypeOfOrganism = OrganismsEnum.SHEEP;
        this.initiative = DEFAULT_INITIATIVE;
        this.strength = DEFAULT_STRENGTH;
    }

    public Sheep(World world, Point position, int strength) {
        super(world, position, strength);
        this.TypeOfOrganism = OrganismsEnum.SHEEP;
        this.initiative = DEFAULT_INITIATIVE;
    }

    @Override
    public String toString() {
        return "Sheep";
    }
}
