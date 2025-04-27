package pl.pg.oop.project2.draw;

import java.awt.*;
import java.awt.event.*;

public class MyMouseAdapter extends MouseAdapter {
    private final BoardPanel board;
    public MyMouseAdapter(BoardPanel board) {
        super();
        this.board = board;
    }
    @Override
    public void mouseClicked(MouseEvent e) {
        int panelWidth = board.getWidth();
        int panelHeight = board.getHeight();
        Point start = new Point((panelWidth-board.getSizeOfTheWorld().x*board.getPANEL_SIZE())/2,
                (panelHeight - board.getSizeOfTheWorld().y*board.getPANEL_SIZE())/2);

        Point clicked = new Point(e.getX(), e.getY());

        for (int i = 0; i < board.getSizeOfTheWorld().x; i++) {
            for (int j = 0; j < board.getSizeOfTheWorld().y; j++) {
                Point position = new Point(start.x + i * board.getPANEL_SIZE(),
                        start.y + j * board.getPANEL_SIZE());

                if (clicked.x >= position.x && clicked.x < position.x + board.getPANEL_SIZE() &&
                        clicked.y >= position.y && clicked.y < position.y + board.getPANEL_SIZE()) {
                    board.showImagePopupMenu(new Point(i, j), e.getComponent(), position);
                    return;
                }
            }
        }
    }
}
