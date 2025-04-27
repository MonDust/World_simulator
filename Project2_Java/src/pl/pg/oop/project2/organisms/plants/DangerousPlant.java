package pl.pg.oop.project2.organisms.plants;

import pl.pg.oop.project2.organisms.Organism;
import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.Plant;
import pl.pg.oop.project2.organisms.World;

import java.awt.*;

public abstract class DangerousPlant extends Plant {
    protected DangerousPlant(World world, Point position) {
        super(world, position);
    }

    @Override
    public void collision(Organism AttackerOrganism) {
        AttackerOrganism.PutIntoWorld();
        world.nullThePosition(position);
        if(AttackerOrganism.getTypeOfOrganism() == OrganismsEnum.HUMAN) {
            world.DeleteHuman();
            world.RemoveOrganismFromList(this);
            return;
        }
        world.RemoveOrganismFromList(AttackerOrganism);
        world.RemoveOrganismFromList(this);
        world.addComment(AttackerOrganism + " ate " + this + " and died.");
    }
}
