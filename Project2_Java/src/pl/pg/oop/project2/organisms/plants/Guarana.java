package pl.pg.oop.project2.organisms.plants;

import pl.pg.oop.project2.organisms.Organism;
import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.Plant;
import pl.pg.oop.project2.organisms.World;

import java.awt.*;

public class Guarana extends Plant {
    public Guarana(World world, Point position) {
        super(world, position);
        this.TypeOfOrganism = OrganismsEnum.GUARANA;
    }

    @Override
    public void collision(Organism AttackerOrganism) {
        AttackerOrganism.PutIntoWorld();
        if(strength > AttackerOrganism.getStrength()) {
            PutIntoWorld();
            if(AttackerOrganism.getTypeOfOrganism() == OrganismsEnum.HUMAN) {
                world.DeleteHuman();
                return;
            }
            world.RemoveOrganismFromList(AttackerOrganism);
            world.addComment(AttackerOrganism + " ate " + this + " and died.");
        }
        else {
            world.RemoveOrganismFromList(this);
            AttackerOrganism.increaseStrength(3);
            world.addComment(AttackerOrganism + " ate " + this + " and got stronger.");
        }
    }

    @Override
    public String toString() {
        return "Guarana";
    }
}
