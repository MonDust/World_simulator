package pl.pg.oop.project2.organisms.animals;

import pl.pg.oop.project2.organisms.Animal;
import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.World;

import java.awt.*;

public class Wolf extends Animal {
    private final static int DEFAULT_INITIATIVE = 5;
    private final static int DEFAULT_STRENGTH = 9;
    public Wolf(World world, Point position) {
        super(world, position);
        this.TypeOfOrganism = OrganismsEnum.WOLF;
        this.initiative = DEFAULT_INITIATIVE;
        this.strength = DEFAULT_STRENGTH;
    }

    public Wolf(World world, Point position, int strength) {
        super(world, position, strength);
        this.TypeOfOrganism = OrganismsEnum.WOLF;
        this.initiative = DEFAULT_INITIATIVE;
    }

    @Override
    public String toString() {
        return "Wolf";
    }
}
