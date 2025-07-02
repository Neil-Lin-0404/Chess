// TODO 到時候新增顏色
// Started Making Date : 2025/7/1
// board[8- toCol][toRow - 'a'] (Important)
#include <bits/stdc++.h>

using namespace std;
// 當一些不合法 或是成功該發的訊息
/*
============================================================================================
                                            訊息
============================================================================================
*/
namespace Messages
{
    void illegalMove()
    {
        cout << "Illegal move!" << endl;
    }
    void illegalAttack()
    {
        cout << "Illegal attack!" << endl;
    }
    void illegalPromotion()
    {
        cout << "Illegal promotion!" << endl;
    }
    void illegalCastle()
    {
        cout << "Illegal castle!" << endl;
    }
    void checkMate()
    {
        cout << "Checkmate!" << endl;
    }
    void moveSuccess()
    {
        cout << "Move successful!" << endl;
    }
    void promotionSuccess()
    {
        cout << "Promotion successful!" << endl;
    }

};
/*
============================================================================================
                                            棋盤
============================================================================================
*/
class Board
{
public:
    vector<vector<char>> board =
        {
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };
    // Board() { init(); }
    // ====================初始化棋盤====================
    void init()
    {
        board = {
            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
            {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    }
    // ====================輸出棋盤====================
    void print() const
    {
        cout << "      W H I T E" << endl;
        cout << "  a b c d e f g h" << endl;
        for (int i = 0; i < 8; ++i)
        {
            cout << 8 - i << " ";
            for (int j = 0; j < 8; ++j)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << "     B L A C K" << endl;
    }
    // ====================判斷是否出界====================
    bool inBounds(char toRow, int toColumn) const
    { // 出界判斷
        if (toRow >= 0 && toRow < 8 && toColumn >= 0 && toColumn < 8)
        {
            cerr << "[DEBUG] InBounds check passed row:" << toRow << " column: " << toColumn << endl;
            return 1;
        }
        cerr << "[DEBUG] InBounds check failed" << endl;
        Messages::illegalMove();
        return 0;
    }
    // 查看輸入的地址row , column 是否有棋子 有則返回true 否則 false
    // ====================看是否已被佔領====================
    bool isOccupied(char toRow, int toCol) const
    { // 是否有棋子
        if (board[8 - toCol][toRow - 'a'] == ' ')
        {
            cerr << "[DEBUG] There is no piece at row: " << toRow << " column: " << toCol << endl;
            return 0; // 沒有棋子
        }
        cerr << "[DEBUG] There is a piece at row: " << toRow << " column: " << toCol << endl;
        cerr << "[DEBUG] Piece: " << board[8 - toCol][toRow - 'a'] << endl;
        return 1;
    }
    // ====================判斷是否同隊====================
    bool onSameTeam(char toRow, int toCol, bool isWhiteTurn) const
    { // 給canAttack 使用，判斷是否同隊
        if (isupper(board[8 - toCol][toRow - 'a']) && !isWhiteTurn || !(isupper(board[8 - toCol][toRow - 'a']) && isWhiteTurn))
        {
            cerr << "[DEBUG] on Same Team check , result : true" << endl;
            return 1; // 同隊
        }
        cerr << "[DEBUG] on Same Team check , result : false" << endl;
        return 0;
    }
    // ====================判斷該棋子是否為現在輪到的選手可移動的====================
    bool canMovePiece(char fromRow, int fromCol, bool isWhiteTurn) const
    {
        char piece = board[8 - fromCol][fromRow - 'a'];
        if (piece == ' ' ||
            isupper(piece) && isWhiteTurn ||
            !isupper(piece) && !isWhiteTurn)
        {
            cerr << "[DEBUG] Unable to move Piece" << endl
                 << " Row: " << fromRow << " Col: " << fromCol << endl;
            cerr << "[DEBUG] Piece: " << board[8 - fromCol][fromRow - 'a'] << endl;
            cerr << "[DEBUG] isWhiteTurn: " << isWhiteTurn << endl;
            return 0; // 無法移動棋子
        }
        cerr << "[DEBUG] Able to Move piece row: " << fromRow << " column: " << fromCol << endl;
        return 1; // 可以移動棋子
    }
    // ====================升變====================
    void promote(char toRow, int toCol, bool isWhiteTurn)
    { // 處理升變
        cerr << "[DEBUG] Executed!" << endl;
        bool changed = false;
        if (!isWhiteTurn)
        {
            char piece;
            while (!changed)
            {
                cout << "Promote to (Q/R/B/N): ";
                cin >> piece;
                cerr << "[DEBUG] User chose: " << piece << endl;
                if (piece == 'Q' || piece == 'R' || piece == 'B' || piece == 'N')
                {
                    board[8 - toCol][toRow - 'a'] = piece; // 更新棋盤
                    cerr << "[DEBUG] Updated!" << endl;
                    changed = true;
                }
                else
                    Messages::illegalPromotion(); // 不合法的升變
            }
        }
        else if (isWhiteTurn)
        {
            char piece;
            while (!changed)
            {
                cout << "Promote to (q/r/b/n): ";
                cin >> piece;
                cerr << "[DEBUG] User chose: " << piece << endl;
                if (piece == 'q' || piece == 'r' || piece == 'b' || piece == 'n')
                {
                    board[8 - toCol][toRow - 'a'] = piece; // 更新棋盤
                    cerr << "[DEBUG] Updated!" << endl;
                    changed = true;
                }
                else
                    Messages::illegalPromotion(); // 不合法的升變
            }
        }
        else
            cerr << "[DEBUG] The upper stuff didn't execute" << endl;
    }
    // ====================移動棋子====================
    void movePiece(char fromRow, int fromCol, char toRow, int toCol)
    { // 直接更新棋盤
        board[8 - toCol][toRow - 'a'] = board[8 - fromCol][fromRow - 'a'];
        board[8 - fromCol][fromRow - 'a'] = ' ';
    }
};
/*
============================================================================================
                                            兵
============================================================================================
*/
// TODO ❗❗❗!!!!待測試!!!!❗❗❗
class Pawn
{
    bool canMove(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn) const
    { // 如果不是同一行
        if (fromRow != toRow)
        {
            // 看是否能攻打
            if (fromCol == toCol)
            {
                cerr << "[DEBUG] Illegal Move at Pawn canMove , second if (fromCol == toCol)" << endl;
                Messages::illegalMove();
                return 0;
            }
            if (canAttack(board, fromRow, fromCol, toRow, toCol, isWhiteTurn))
                board.movePiece(fromRow, fromCol, toRow, toCol);
            else
            {
                cerr << "[DEBUG] at First if-> second if-> else" << endl;
                Messages::illegalMove();
                return false; // 不是斜對角
            }
            Messages::moveSuccess();
            return true;
        }
        if (isWhiteTurn)
        {
            if (abs(fromRow - toRow) == 1)
            {
                if (board.isOccupied(toRow, toCol))
                    return false;                                // 假設這裡是偵測是有棋子
                board.movePiece(fromRow, fromCol, toRow, toCol); // 移動棋子
                Messages::moveSuccess();
                if (canPromote(board, fromRow, fromCol, toRow, toCol, isWhiteTurn))
                {
                    board.promote(toRow, toCol, isWhiteTurn); // 處理升變
                } // 處理升變
                return true;
            }
        }
        return false;
    }
    bool canAttack(Board &board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn) const
    {
        if (isWhiteTurn)
        {
            if (abs(fromRow - toRow) == 1 && abs(fromCol - toCol == 1)) // 這裡看是否為斜對角
            {
                if (board.isOccupied(toRow, toCol)) // 這裡是偵測是否有棋子
                {
                    if (board.onSameTeam(toRow, toCol,isWhiteTurn)) // 這裡是偵測是否同隊
                    {
                        Messages::illegalAttack();
                        return false; // 同隊不能攻擊
                    }
                    return true; // 可以攻擊
                }
            }
        }
        return false;
    }
    bool canPromote(Board board, char fromRow, int fromCol, char toRow, int toCol, bool isWhiteTurn) const
    {
        if(toCol == 1 || toCol == 8)
        {
            board.promote(toRow, toCol, isWhiteTurn); // 處理升變
            Messages::promotionSuccess();
            return 1; // 返回1代表升變成功
    }
        else return 0;
    }
};
/*
============================================================================================
                                            車
============================================================================================
*/
class Rook
{
};
/*
============================================================================================
                                            馬
============================================================================================
*/
class Knight
{
};
/*
============================================================================================
                                            主教
============================================================================================
*/
class Bishop
{
};
/*
============================================================================================
                                            后
============================================================================================
*/
class Queen
{
};
/*
============================================================================================
                                            王
============================================================================================
*/
class King
{
};
/*
============================================================================================
                                            主要
============================================================================================
*/
int main()
{
    Board chessBoard;
    chessBoard.print();
    chessBoard.promote('a', 1, true);
    chessBoard.print();
    return 0;
}

