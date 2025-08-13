#include <iostream>

using namespace std;

void initStatus(int *s)
{
    cout << "HP와 MP를 입력해주세요: ";
    cin >> s[0] >> s[1];
    while (*s < 51 || *(s + 1) < 51)
    {
        cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요.\n";
        cin >> s[0] >> s[1];
    }

    cout << "공격력과 방어력을 입력해주세요: ";
    cin >> s[2] >> s[3];
    while (s[2] < 1 || s[3] < 1)
    {
        cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요.\n";
        cin >> s[2] >> s[3];
    }
}

void setPotion(int count, int *p_HPPotion, int *p_MPPotion)
{
    cout << "* 포션이 지급되었습니다. (HP, MP 포션 각 5개)\n";

    *p_HPPotion = count;
    *p_MPPotion = count;
}

void initGame(int *s, int *p_HPPotion, int *p_MPPotion)
{
    setPotion(5, p_HPPotion, p_MPPotion);
}

void usePotion(bool isHP, int *p_status, int *p_Potion)
{
    // Check Potion Count
    if (*p_Potion < 1)
    {
        cout << "포션이 부족합니다.\n";
        return;
    }

    // Use potion
    *p_status += 20;
    (*p_Potion)--;

    cout << "* " << (isHP ? "HP" : "MP") << "가 20 회복되었습니다. 포션이 1개 차감됩니다.\n";
    cout << "현재 " << (isHP ? "HP: " : "MP: ") << *p_status << "\n남은 포션 수: " << *p_Potion << endl;
}

void upgradeStat(bool isHP, int *p_status)
{
    *p_status *= 2;

    cout << "* " << (isHP ? "HP" : "MP") << "가 2배로 증가했습니다.\n";
    cout << "현재 " << (isHP ? "HP: " : "MP: ") << *p_status << endl;
}

void useSkill(bool isUltimateSkill, int *p_MPStatus)
{
    if (isUltimateSkill == false && *p_MPStatus < 50)
    {
        cout << "스킬 사용이 불가합니다.\n";
        return;
    }

    (isUltimateSkill) ? (*p_MPStatus *= 0.5) : (*p_MPStatus -= 50);

    cout << "* 스킬을 사용하여 MP가 50" << (isUltimateSkill ? "%" : "") << "소모되었습니다.\n";
    cout << "현재 MP: " << *p_MPStatus << endl;
}

void startGame(int *s, int *p_HPPotion, int *p_MPPotion)
{
    int opt = 0;
    initStatus(s);
    initGame(s, p_HPPotion, p_MPPotion);

    cout << "<스탯 관리 시스템>\n1. HP 회복\n2. MP 회복\n3. HP 강화\n4. MP 강화\n5. 공격 스킬 사용\n6. 필살기 사용\n7. 나가기\n";
    while (opt != 7)
    {
        cout << "번호를 택해주세요: ";
        cin >> opt;

        switch (opt)
        {
        case 1:
        case 2:
            usePotion(opt == 1, s + (opt == 1 ? 0 : 1), (opt == 1 ? p_HPPotion : p_MPPotion));
            break;
        case 3:
        case 4:
            upgradeStat(opt == 3, s + (opt == 3 ? 0 : 1));
            break;
        case 5:
        case 6:
            useSkill(opt == 6, s + 1);
            break;
        case 7:
            cout << "프로그램을 종료합니다." << endl;
            break;

        default:
            break;
        }
    }
}

int main()
{
    int s[] = {0, 0, 0, 0};
    int p_HPPtion = 0;
    int p_MPPtion = 0;

    startGame(s, &p_HPPtion, &p_MPPtion);
}