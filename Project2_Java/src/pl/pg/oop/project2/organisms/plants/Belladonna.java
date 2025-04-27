package pl.pg.oop.project2.organisms.plants;

import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.World;

import java.awt.*;

public class Belladonna extends DangerousPlant {
    private final static int DEFAULT_STRENGTH = 99;
    public Belladonna(World world, Point position) {
        super(world, position);
        this.TypeOfOrganism = OrganismsEnum.BELLADONNA;
        this.strength = DEFAULT_STRENGTH;
    }

    @Override
    public String toString() {
        return "Belladonna";
    }
}
