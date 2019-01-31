// Room: /d/xingxiu/xx1.c
// Update by caiji@SJ 8/24/2000

inherit ROOM;

void create()
{
    set("short", "ɽǰ�ĵ�");
    set("long", @LONG
��վ��ʯɽǰ�Ļĵ��ϡ�����˼�������������ȥ�����ǿ����ܲݡ�
˷����ɱ�������ľ�������·���м������޵�����������ͬʱ����������
һ��һ������û�£����ǿ�ذɡ�
LONG);

    set("objects", ([
          __DIR__"npc/feitian" : 1,
         __DIR__"npc/xxdizi" : 1,
    ]));

    set("exits", ([
          "northup" : __DIR__"ryd1",
          "northwest" : __DIR__"xx2",
          "south" : __DIR__"xxh2",
          "northeast" : __DIR__"rukou",
      ]));

    set("outdoors", "xingxiuhai");

    set("coor/x",-300);
  set("coor/y",170);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam = (mapping)me->query("family");

   if (dir =="northup" && present("feitian zi", environment(me)) &&
       (!myfam || myfam["family_name"] != "������") && me->query("combat_exp") < 100000) 
         return notify_fail("�����ӵ�ס���㣺������������а�ɵ�����ô����ȥ�ݼ��������ɣ�\n");
            
   return ::valid_leave(me, dir);
}
