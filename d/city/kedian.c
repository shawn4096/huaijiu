// /d/city/kedian.c

inherit ROOM;

void create()
{
	set("short", "������ջ");
	set("long", @LONG       
���Ǳ�����ջ���ϰ�����ǳ���¡������οͶ�ѡ��������ţ��������
������������صķ������顣��С����������æ������ת���Ӵ�����ǻ������
���ˡ��������˽�������С����æӭ��ǰȥ����ջ�����ǽ�Ϲ���һ����Ŀ��
����(paizi)��
LONG
	);

	set("valid_startroom", 1);
        set("no_sleep_room",1);
set("no_fight",1);
	set("item_desc", ([
		"paizi" : "¥���ŷ���ÿҹ����������\n",
	]));

	set("objects", ([
         __DIR__"npc/xiaoer" : 1,
               "/clone/npc/xu" :1,
	]));

	set("exits", ([
         "east" : __DIR__"kedian/pianting",
          "west" : __DIR__"beidajie2",
		"up" : __DIR__"kedian2",
	]));

	set("coor/x",130);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",130);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",130);
  set("coor/y",10);
   set("coor/z",0);
   setup();
	"/clone/board/kedian_b"->foo();
}

int valid_leave(object me, string dir)
{

	if ( !me->query_temp("rent_paid") && dir == "up" )
		return notify_fail("��ô�ţ����ס����\n");

	if ( me->query_temp("rent_paid") && dir == "west" )
		return notify_fail("�͹��Ѿ��������ӣ���ô��ס��������أ����˻���ΪС���ź����أ�\n");

	return ::valid_leave(me, dir);
}
