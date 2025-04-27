package pl.pg.oop.project2.organisms.plants;

import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.Plant;
import pl.pg.oop.project2.organisms.World;

import java.awt.*;

public class Grass extends Plant {
    public Grass(World world, Point position) {
        super(world, position);
        this.TypeOfOrganism = OrganismsEnum.GRASS;
    }

    @Override
    public String toString() {
        return "Grass";
    }
}

