// road3.c by XiaoYao

inherit ROOM;
void create()
{
        set("short","�ּ��");
        set("long",@LONG
������һ���ּ�С���������������ѡ������ǹ����ˡ�����ɽ
��ï�ܣ�������棬��λ��·Ҫʮ��С�ġ�
LONG);
        set("outdoors", "��ɽ");
        set("exits",([ /* sizeof() == 1 */
            "east"      : __DIR__"road2",
            "northwest" : __DIR__"road4",
        ]));
        set("no_clean_up", 0);
        set("coor/x",-60);
  set("coor/y",-530);
   set("coor/z",0);
   setup();
}


