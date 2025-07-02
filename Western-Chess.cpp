// TODO 到時候新增顏色
// Started Making Date : 2025/7/1
#include <bits/stdc++.h>

using namespace std;
// 當一些不合法 或是成功該發的訊息
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
// 兵的規則
class Pawn
{
public:
    // 大概的偵測架構
    /*
    canMove -> 偵測是否為斜對角
    是 則進入canAttack
    否則 偵測移動距離是否唯一格
        是 則move
        否則偵測是否為兩格
            是 則看是不是第一步
            否則不合法
    */
    // 是否可移動
    bool canMove(Board &board, int fromRow, char fromCol, int toRow, char toCol, bool isWhiteTurn) const
    { // 如果不是同一行
        if (fromRow != toRow)
        {
            // 看是否能攻打
            if (canAttack(board, fromRow, fromCol, toRow, toCol, isWhiteTurn))
                board.movePiece(fromRow, fromCol, toRow, toCol);
            else
            {
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
                if (board.isOccupied(toRow, toCol, isWhiteTurn))
                    return false;                                // 假設這裡是偵測是否有棋子
                board.movePiece(fromRow, fromCol, toRow, toCol); // 移動棋子
                Messages::moveSuccess();
                if (canPromote(board, fromRow, fromCol, toRow, toCol, isWhiteTurn))
                {
                    board.promote(board, toRow, toCol,isWhiteTurn); // 處理升變
                } // 處理升變
                return true;
            }
        }
        return false;
    }
    // 是否可攻擊
    // canAttack 要處理是否是row 和 col 都有移動 且合法
    bool canAttack(Board &board, int fromRow, char fromCol, int toRow, char toCol, bool isWhiteTurn) const
    {
        if (isWhiteTurn)
        {
            if (abs(fromRow - toRow) == 1 && (fromCol - toCol == 1 || fromCol - toCol == -1))
            {
                if (board.isOccupied(toRow, toCol, isWhiteTurn)) // 假設這裡是偵測是否有棋子
                {
                    if (board.onSameTeam(toRow, toCol, fromRow, fromCol, isWhiteTurn)) // 假設這裡是偵測是否同隊
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
    // 升變 ,車、馬、象或后
    // 看tocol toRow 是否為空 且是否為8 或 0
    bool canPromote(Board board, int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn) const
    {
        if(toCol == 1 || toCol == 8)
        {
            board.promote(board, toRow, toCol, isWhiteTurn); // 處理升變
            Messages::promotionSuccess();
            return 1; // 返回1代表升變成功
    }
        else return 0;
    }
    bool canEnPassant() const
    {
    }
};
// 車的規則
class Rook
{
public:
    bool canMoveOrAttack(Board &board, int fromRow, char fromCol, int toRow, char toCol, bool isWhiteTurn) const
    {
    }
};
// 馬的規則
class Knight
{
public:
    bool canMoveOrAttack(Board &board, int fromRow, char fromCol, int toRow, char toCol, bool isWhiteTurn) const
    {
    }
};
// 象的規則
class Bishop
{
public:
    bool canMoveOrAttack(Board &board, int fromRow, char fromCol, int toRow, char toCol, bool isWhiteTurn) const
    {
    }
};
// 后的規則
class Queen
{
public:
    bool canMoveOrAttack(Board &board, int fromRow, char fromCol, int toRow, char toCol, bool isWhiteTurn) const
    {
    }
};
// 王的規則
class King
{
public:
    bool canMoveOrAttack(Board &board, int fromRow, char fromCol, int toRow, char toCol, bool isWhiteTurn) const
    {
    }
    bool checkMate() const
    {
    }
};
// 棋盤相關 : 升位 , 吃子 , 初始化棋盤 , 將死 , 王車易位處理
class Board
{
    vector<vector<char>> chessBoard; // 8×8
public:                              // ← 加 public
    Board() { init(); }

    void init()
    { // 不用參數、直接填自己的棋盤
        chessBoard = {
            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
            {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
    }

    void print() const
    { // 直接用成員資料
        cout << "     W H I T E  \n";
        cout << "  a b c d e f g h\n";
        for (int i = 0; i < 8; ++i)
        {
            cout << 8 - i << ' ';
            for (int j = 0; j < 8; ++j)
                cout << chessBoard[i][j] << ' ';
            cout << '\n';
        }
        cout << "    B L A C K  \n";
    }

    bool inBounds(char row, int column) const
    { // 出界判斷
        return row >= 0 && row < 8 && column >= 0 && column < 8;
    }

    bool isOccupied(int toRow, char toCol, bool isWhiteTurn) const
    { // 是否有棋子
        if(chessBoard[toCol][toRow] == ' ')
            return 0; // 沒有棋子
        return 1;
    }
    bool onSameTeam(int toRow, int toCol, int fromRow, int fromCol, bool isWhiteTurn) const
    { // 給canAttack 使用，判斷是否同隊
    }
    bool canMove(char fromRow,int toCol,bool isWhiteTurn) const
{
}
    bool canAttack() const
    { // 判斷是否可以攻擊
    }
    void promote(Board board, int toRow, int toCol, bool isWhiteTurn)
    { // 處理升變
        if (!isWhiteTurn)
        {
            char piece;
            while (0)
            {
                cout << "Promote to (Q/R/B/N): ";
                cin >> piece;
                piece = toupper(piece); // 轉大寫
                if (piece == 'Q' || piece == 'R' || piece == 'B' || piece == 'N')
                    chessBoard[toRow][toCol] = piece; // 更新棋盤
                else
                    Messages::illegalPromotion(); // 不合法的升變
                    continue; // 重新輸入
            }
            
        }
        else
        {
            char piece;
            while (0)
            {
                cout << "Promote to (q/r/b/n): ";
                cin >> piece;
                piece = tolower(piece); // 轉大寫
                if (piece == 'q' || piece == 'r' || piece == 'b' || piece == 'n')
                    chessBoard[toRow][toCol] = piece; // 更新棋盤
                else
                    Messages::illegalPromotion(); // 不合法的升變
                    continue; // 重新輸入
            }
            
        }
    }
    bool canCastle() const
    { // 判斷是否可以王車易位
    }
    void movePiece(int fromRow, char fromCol, int toRow, char toCol)
    { // 直接更新棋盤
        chessBoard[toRow][toCol] = chessBoard[fromRow][fromCol];
        chessBoard[fromRow][fromCol] = ' ';
    }
};

int main()
{
    Board chessBoard;
    chessBoard.print();
    return 0;
}
