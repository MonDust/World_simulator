package pl.pg.oop.project2.organisms.animals;

import pl.pg.oop.project2.organisms.Animal;
import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.World;

import java.awt.*;

public class Antelope extends Animal {
    private final static int DEFAULT_INITIATIVE = 4;
    private final static int DEFAULT_STRENGTH = 4;
    private final static int DEFAULT_STEPS = 2;

    public Antelope(World World_, Point Position_) {
        super(World_, Position_);
        TypeOfOrganism = OrganismsEnum.ANTELOPE;
        initiative = DEFAULT_INITIATIVE;
        strength = DEFAULT_STRENGTH;
        step = DEFAULT_STEPS;
    }

    public Antelope(World world, Point position, int strength) {
        super(world, position, strength);
        this.TypeOfOrganism = OrganismsEnum.ANTELOPE;
        this.initiative = DEFAULT_INITIATIVE;
        step = DEFAULT_STEPS;
    }

    @Override
    public String toString() {
        return "Antelope";
    }
}
