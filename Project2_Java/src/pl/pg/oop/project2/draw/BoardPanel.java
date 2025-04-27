package pl.pg.oop.project2.draw;

import pl.pg.oop.project2.organisms.NamesOfOrganisms;
import pl.pg.oop.project2.organisms.Organism;
import pl.pg.oop.project2.organisms.OrganismsEnum;
import pl.pg.oop.project2.organisms.World;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.HashMap;
import java.util.Map;

public class BoardPanel extends JPanel implements NamesOfOrganisms {
    private static final int BORDER_SIZE = 1;
    private static final double PANEL_SIZE_RATIO = 0.9;
    private final int PANEL_SIZE;
    private final int IMAGE_SIZE;
    private final Point SizeOfTheScreen;
    private final Point SizeOfTheWorld;
    private final Map<Point, ImageIcon> ImageMap;

    World world;

    public BoardPanel(Point SizeOfTheScreen, Point SizeOfTheWorld, World world) {
        this.SizeOfTheScreen = SizeOfTheScreen;
        this.SizeOfTheWorld = SizeOfTheWorld;
        PANEL_SIZE = (int)((double)(SizeOfTheScreen.y/SizeOfTheWorld.y)*PANEL_SIZE_RATIO);
        IMAGE_SIZE = PANEL_SIZE - BORDER_SIZE;
        ImageMap = new HashMap<>();
        this.world = world;
        loadImageIcons();
        initializeMouseListener();
        initializeKeyListener();
    }

    public int getPANEL_SIZE() {
        return PANEL_SIZE;
    }

    public Point getSizeOfTheScreen() {
        return SizeOfTheScreen;
    }

    public Point getSizeOfTheWorld() {
        return SizeOfTheWorld;
    }

    public void loadImageIcons() {
        for (int i = 0; i < SizeOfTheWorld.x; i++) {
            for (int j = 0; j < SizeOfTheWorld.y; j++) {
                Organism organism = world.getOrganismInPosition(new Point(i,j));
                if(organism != null) {
                    ImageMap.put(new Point(i, j), organism.getImage());
                } else {
                    ImageMap.put(new Point(i, j), new ImageIcon("Images/Ground.jpg"));
                }
            }
        }
    }

    private void initializeMouseListener() {
        MouseAdapter mouseAdapter = new MyMouseAdapter(this);

        addMouseListener(mouseAdapter);
    }

    private void initializeKeyListener() {
        KeyListener keyListener = new MyKeyListener(this);
        addKeyListener(keyListener);
        setFocusable(true);
        requestFocusInWindow();
    }

    public void showImagePopupMenu(Point OrganismPosition, Component component, Point MenuPosition) {
        if(!world.checkIfNotOccupied(OrganismPosition)) return;
        JPopupMenu popupMenu = new JPopupMenu();

        String PathToImg = "Images/";
        for(int i = 0; i < NumberOfOrg; i++) {
            String Name = NameOfOrg[i];
            OrganismsEnum OrgEnum = OrganismsEnum.values()[i];
            JMenuItem Item = new JMenuItem(Name);
            Item.addActionListener((ActionEvent e) -> {
                setImageAtPosition(OrganismPosition, PathToImg+Name+".jpg");
                world.AddOrganism(OrgEnum, OrganismPosition);
            });
            popupMenu.add(Item);
        }
        popupMenu.show(component, MenuPosition.x, MenuPosition.y);
    }

    private void setImageAtPosition(Point OrganismPosition, String ImagePath) {
        ImageIcon imageIcon = new ImageIcon(ImagePath);
        ImageMap.put(OrganismPosition, imageIcon);
        repaint();
    }


    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        int panelWidth = getWidth();
        int panelHeight = getHeight();
        Point start = new Point((panelWidth - SizeOfTheWorld.x * PANEL_SIZE) / 2,
                (panelHeight - SizeOfTheWorld.y * PANEL_SIZE) / 2);

        for (int i = 0; i < SizeOfTheWorld.x; i++) {
            for (int j = 0; j < SizeOfTheWorld.y; j++) {
                Point ImagePosition = new Point(start.x + i * PANEL_SIZE,
                        start.y + j * PANEL_SIZE);

                ImageIcon ImageIcon = ImageMap.get(new Point(i, j));

                if (ImageIcon != null) {
                    Image image = ImageIcon.getImage();
                    g.drawImage(image, ImagePosition.x, ImagePosition.y, IMAGE_SIZE, IMAGE_SIZE, null);
                }

                g.setColor(Color.DARK_GRAY);
                g.drawRect(ImagePosition.x, ImagePosition.y, PANEL_SIZE, PANEL_SIZE);
            }
        }
    }

    @Override
    public Dimension getPreferredSize() {
        int panelWidth = SizeOfTheWorld.x * PANEL_SIZE;
        int panelHeight = SizeOfTheWorld.y * PANEL_SIZE;
        return new Dimension(panelWidth, panelHeight);
    }


}
