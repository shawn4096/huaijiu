// Room: /dali/xiulou.c
// bbb 1997/06/11
// Modify By River 98/12/
inherit ROOM;

void create()
{
	set("short", "��¥");
	set("long", @LONG
�����¥�ѿ��˼�ʮ���ˣ�������ϰ�������������ԭѧ������֯������
������ҵ꣬�ö���Ǯ�˶������������װ���������(list)����������û
�����õ��·�����
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
            "east" : __DIR__"xijie2",
        ]));

	set("objects", ([
		__DIR__"npc/dasao": 1,
                __DIR__"npc/women": 1,
        ]));
	set("coor/x",-340);
  set("coor/y",-400);
   set("coor/z",-20);
   setup(); 
}

void init()
{
     object me = this_player();
     if(me->query_temp("xuncheng")){
      me->set_temp("dali_xc/xiulou",1);
      }
}
