//road4.c by Xiaoyao

inherit ROOM;
void create()
{
        set("short","�ּ��");
        set("long",@LONG
������һ���ּ�С���������������ѡ������ǹ����ˡ�����ɽ
��ï�ܣ�������棬��λ��·Ҫʮ��С�ġ�
LONG);
        set("objects", ([
           __DIR__"npc/snake": 1,
        ]));
        set("outdoors", "��ɽ");
        set("exits",([ /* sizeof() == 1 */
            "southwest" : __DIR__"road5",
            "southeast" : __DIR__"road3",
        ]));
        set("coor/x",-70);
  set("coor/y",-520);
   set("coor/z",0);
   setup();
}

