package pl.pg.oop.project2.organisms.plants;

import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.Plant;
import pl.pg.oop.project2.organisms.World;

import java.awt.*;

public class Sow_Thistle extends Plant {
    private final static int TRY_TO_SPREAD = 3;
    public Sow_Thistle(World world, Point position) {
        super(world, position);
        this.TypeOfOrganism = OrganismsEnum.SOW_THISTLE;
    }

    @Override
    public boolean action() {
        boolean Flag = false;
        for(int i = 0; i < TRY_TO_SPREAD; i++) {
            if(Flag) break;
            Flag = super.action();
        }
        return Flag;
    }

    @Override
    public String toString() {
        return "Sow_Thistle";
    }
}
