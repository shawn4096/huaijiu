// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�˴�������أ����������ƥ�Ѳ�����ǰ������˵��������
����̩ɽ��������������������ʣ������˰���Ҫ�ĳ�С��
��ɽ��
LONG
        );

        set("exits", ([
                "northup" : __DIR__"ertian",
                "southdown" : __DIR__"shijin",
        ]));

        set("objects",([
        __DIR__"npc/jian-ke2" : 1,
        ]));
        set("outdoors", "taishan");
        set("coor/x",170);
  set("coor/y",160);
   set("coor/z",50);
   set("coor/x",170);
  set("coor/y",160);
   set("coor/z",50);
   setup();
}

int valid_leave(object me, string dir)
{
        if (dir=="northup" )
        {
        if(me->query("can_ride"))
                {
                                        return 0;

                }
        
        if(me->query_temp("ride_horse"))
        return notify_fail("��λ" + RANK_D->query_respect(me) + "����������������ɽ�ɣ�\n");
        }
        return ::valid_leave(me, dir);
}

