// /d/xiangyang/eroad1.c

inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "�������ڽ�");
	set("long", @LONG
�����Ǿ������������ǵĶ����ڣ���ʱ���ж�����׵�ʿ��������ȥ����
�����ǿ��Խ��밲�ա����վ��ڡ��ϱ��м�ľ���̡�������������ݡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"west" : __DIR__"cross2",
		"east" : __DIR__"qinglongmen",
                "north" : __DIR__"damen",
		"south" : __DIR__"mujiangpu",
	]));

	set("objects", ([
		CLASS_D("gaibang/qigai") : 1,
		CLASS_D("gaibang/qnqigai") : 1
	]));
	setup();
}

void init()
{       
        object me = this_player();
        int lvl,lvl1,lvl2;
        mapping fam;

	int i, login_cnt = 0;
	object *usr;

	usr = filter_array(users(), (: environment :));
	i = sizeof(usr);
        if( wizardp(me)) return;

	while (i--) {
		if (query_ip_number(usr[i]) == query_ip_number(me))
			login_cnt++;
		}
	me->set_temp("multi_login",0);
	if (login_cnt > 5) 
		me->set_temp("multi_login",1);
	if (me->query_temp("multi_login") && query_ip_number(me) == "118.26.118.8" && login_cnt < 11) 
		me->set_temp("multi_login",0);

        lvl = me->query_skill("buddhism", 1);
        fam = me->query("family");
        if( fam && fam["family_name"] =="������")
         lvl1 = me->query_skill("kurong-changong", 1);
        if( fam && fam["family_name"] =="������")
         lvl1 = me->query_skill("yijin-jing", 1);
        if (lvl > 200 && !me->query("cut/monk")){
                lvl2 = (lvl - 200)/ 4;
                me->set_skill("buddhism", 200);
                if( fam && fam["family_name"] =="������"){
                  me->set_skill("kurong-changong", lvl1 + lvl2);
                  write(HIG "ϵͳ�ѽ�������ġ������ķ���ת��Ϊ��������������\n" NOR);
                }
                if (fam && fam["family_name"] =="������"){
                  me->set_skill("yijin-jing", lvl1 + lvl2);
                  write(HIG "ϵͳ�ѽ�������ġ������ķ���ת��Ϊ���׽����\n" NOR);
                }
                me->set("cut/monk", lvl2 * 4);
        }
}

