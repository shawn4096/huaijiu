// Room: /d/shaolin/dmyuan2.c
// Date: YZC 96/01/19

inherit ROOM;

void init()
{
	add_action("lingwu","lingwu");
}


void create()
{
	set("short", "��ĦԺ���");
	set("long", @LONG
����һ�����ӵĵ��á����׵�ǽ�Ϲ����˸����书ͼ�ף����ٰ����ü
����ɮ����������ͼ�׻���֮ǰ���ƺ��ڿ��˼�����ϱ�ɽǽ�Ǹ߼��ݶ���
����ܣ��߽�ϸ���������Ǹ��Ÿ��ɵ��书���ţ������а��ż��Ű���ڭ��
�������ţ���λ��ɮ�����붨�С�
LONG
);

	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"dmyuan",
	]));

	
	set("coor/x",20);
	set("coor/y",440);
	set("coor/z",130);
	setup();
}

int lingwu(string arg)
{
	object me=this_player();
	string special;
	int bl,sl,i;

	if (!me->query("luohan_winner")) {
		write("�㼶�𲻹��������ڴ�����\n");
		return 1;
	}
	if (!arg) {
		write("��Ҫ����ʲô��\n");
		return 1;
	}
	if (!me->query_skill(arg,1)) {
		write("�㲻�����ּ��ܡ�\n");
		return 1;
	}
	if (me->is_busy() || me->is_fighting()) {
		write("����æ���ء�\n");
		return 1;
	}
	if (arg == "force" && me->query_skill("force",1)<200) {
		write("�������ڵĻ����ڹ���Ϊ�����޷���������ڹ���\n");
		return 1;
	}
	if((int)me->query("potential") < 1 ) {
		write("���ʵս�еõ���Ǳ���Ѿ������ˡ�\n");
		return 1;
	}
	if (!(special=me->query_skill_mapped(arg))) {
		write("��ֻ�ܴ����⼼��������\n");
		return 1;
	}
	bl=me->query_skill(arg,1);
	if (bl > me->query("jing") || me->query("jing")*100/me->query("max_jing") < 50) {
		me->receive_damage("jing",bl/5);
		write("��û�취���о���\n");
		return 1;
	}
	sl=me->query_skill(special,1);
	if (bl > sl) {
		write("���"+to_chinese(special)+"���費�����޷��������һ���"+to_chinese(arg)+"��\n");
		return 1;
	}
	write("���˼���룬��"+to_chinese(arg)+"�����������һ�㡣\n");
	i =me->query_int() + me->query_skill("literate", 1)/10;
	if (me->query("combat_exp",1) >850000){
		me->receive_damage("jing",bl/5*3);
		me->add("potential",-random(2));
		me->improve_skill(arg, i*5/3);
		if(me->query("age")<30)me->improve_skill(arg,30-me->query("age"));
		if(me->query("age")>60)me->improve_skill(arg,me->query("age")-60);
		return 1;
	}
	me->receive_damage("jing",bl/5*2);
	me->add("potential", -random(2));
	me->improve_skill(arg, i*3/2);
	return 1;
}
