// Room: /d/dzd/shidong2.c


inherit ROOM;
void create()
{
	set("short","����ʯ��");
	set("long",@LONG
��Ȼ�γɵ�����ʯ���������еĵضκ�ֱ���еĵض��ֺ��䣻�еĵض�����԰�еľ���
���ȣ�����ǰ�������г���ɽǰ����·֮�棻���еĵض����������ľ�������������������
��������һ��֮�С����й����������������ȷ紵����
LONG
	);
	set("exits",([
		"east" : __DIR__"shidong3",
		"west" : __DIR__"shidong1",
		"north" : __DIR__"shidong4",
		"south" : __DIR__"rukou",
	]));
	set("objects",([
		__DIR__"npc/bear" : random(1),
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
