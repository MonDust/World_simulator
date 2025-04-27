package pl.pg.oop.project2;

import java.awt.*;
import javax.swing.*;

import pl.pg.oop.project2.draw.MyFrame;
import pl.pg.oop.project2.organisms.*;
public class Main {

    public final static Point SizeOfTheWorld = new Point(20, 15);
    public static void main(String[] args) {
        World world = new World(SizeOfTheWorld);
        SwingUtilities.invokeLater(() -> new MyFrame(world));
    }
}