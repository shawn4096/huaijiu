// Room: /d/dzd/shidong1.c

inherit ROOM;
void create()
{
	set("short","����ʯ��");
	set("long",@LONG
����һ����Ȼ�γɵ�����ʯ���������еĵضκ�ֱ���еĵض��ֺ��䣻�еĵض�����԰�еľ�����
�ȣ�����ǰ�������г���ɽǰ����·֮�棻���еĵض����������ľ�������������������
��������һ��֮�С����й����������������ȷ紵����
LONG
	);
	set("exits",([
		"northeast" : __DIR__"shidong4",
		"east" : __DIR__"shidong2",
		"southeast" : __DIR__"rukou",
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object ob;
	string name;
	me = this_player();
	name = me->query("id")+"'s boss";

	ob = present(name,environment(me) );
	if(ob)  return notify_fail(ob->query("name")+"һ�ѽ�����ס�������ܣ�\n" );
	return ::valid_leave(me, dir);
}
