//road2.c by XiaoYao

inherit ROOM;
void create()
{
        set("short","�ּ��");
        set("long",@LONG
������һ���ּ�С���������������ѡ������ǹ����ˡ�����ɽ
��ï�ܣ�������棬��λ��·Ҫʮ��С�ġ�
LONG);
        set("objects", ([
           __DIR__"obj/shikuai": 1,
        ]));
        set("outdoors", "��ɽ");
        set("exits",([ /* sizeof() == 1 */
            "west" : __DIR__"road3",
            "east" : __DIR__"road1",
        ]));
        set("coor/x",-50);
  set("coor/y",-530);
   set("coor/z",0);
   setup();
}

