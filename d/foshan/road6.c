//road6.c by XiaoYao

inherit ROOM;
void create()
{
        set("short","�ּ��");
        set("long",@LONG
������һ���ּ�С���������������ѡ������ǹ����ˡ�����ɽ
��ï�ܣ�������棬��λ��·Ҫʮ��С�ġ�
LONG);
        set("objects", ([
           __DIR__"obj/hua1": 1,
        ]));
        set("outdoors", "foshan");
        set("exits",([ /* sizeof() == 1 */
        "west"  : "/d/dali/dalisouth/jiangbei",
            "east"  : __DIR__"road5",
        ]));
        set("coor/x",-90);
  set("coor/y",-530);
   set("coor/z",0);
   setup();
}


