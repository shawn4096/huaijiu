// Room: /d/shaolin/cjlou.c
// Date: YZC 96/01/19

inherit ROOM;




void create()
{
	set("short", "�ؾ���һ¥");
	set("long", @LONG
�����������������--���ֲؾ��󡣲���Ϊ��ԭ�𷨵���Դ�������´�
���ؾ�֮�������º�����ƥ�����ﶼ���������飬�߼��������ܣ���ܼ�
��������һ��ͨ�еĿ�϶�����Ŵ�����м䣬����ط������ɳ���������Ŀ
�⼰�����㿴�����Ϸ��˼����𾭡�
LONG
	);

	set("exits", ([
		"out" : __DIR__"xiaoxi1",
		"up" : __DIR__"cjlou1",
	]));

	set("objects",([
		CLASS_D("shaolin") + "/dao-yi" : 1,
//		"d/shaolin/obj/fojing1"+random(2) : 1,
//		"d/shaolin/obj/fojing2"+random(2) : 1,
	]));

	set("coor/x",100);
  set("coor/y",370);
   set("coor/z",160);
   setup();
}


int valid_leave(object me, string dir)
{
	if (me->query("family/family_name") == "����Ľ��" && me->query("family/generation") <3);
	else if (me->query("family/family_name") == "������" && me->query("family/generation") <36);
        else if( !present("shou yu", me) && (objectp(present("daoyi chanshi", environment(me)))) )
		if (dir == "up" ) return notify_fail("��һ˵��: ��δ����ɣ������϶�¥��\n");
	return ::valid_leave(me, dir);
}
