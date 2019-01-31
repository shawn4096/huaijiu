inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;
#include <ansi.h>

string ask_rob();

string *skill = ({ 
	"longzhua-gong", "ruying-suixingtui", "yizhi-chan", "jingang-quan",
	"qianye-shou", "nianhua-zhi", "zhenshan-mianzhang", "jieshou-jiushi",
	"yiyang-zhi", "qishang-quan", "lanhua-shou", "poyu-quan",
	"xianglong-zhang", "huagu-mianzhang", "jiuyin-baiguzhua", "anran-zhang",
	}); 

string *force = ({
	"yijin-jing", "yijin-jing", "yijin-jing", "yijin-jing",
	"yijin-jing", "yijin-jing", "yinyun-ziqi", "linji-zhuang",
	"qiantian-yiyang", "shenghuo-shengong", "bihai-chaosheng","zixia-gong",
	"huntian-qigong", "dulong-dafa", "linji-zhuang", "yunu-xinjing",
	});

string *perform = ({
	"canyun", "ruying", "wofo", "fumo",
	"qianshou", "fuxue", "bingdi", "foguang",
	"sandie", "qishang", "fuxue", "leidong",
	"paiyun", "bujue", "jiuyin", "anran",
	});

string *base = ({
	"claw", "leg", "finger", "cuff",
	"hand", "finger", "strike", "hand",
	"finger", "cuff", "hand", "cuff",
	"strike", "strike", "claw", "strike",
	}); 

void create()
{
    set_name("����", ({ "hufa zhanglao", "hufa", "zhanglao"}));

	set("init",0);
	
    set("gender", "����");
    set("age", 20 + random(60));
    set("long", "����һλ���ָ��֡�\n"
    	+ "��������̳�İ�ȫ��\n" );
	set("no_get", "�������϶������̫���ˡ�\n");
	if( random(10) < 2 )
		set("double_attack",1);

    set("inquiry", ([
        "����"          		: (: ask_rob :),
        ]));

}       

void init()
{
    object ob1;
	object ob = environment(this_object());
	int lvl = ob->query("skill_lvl");
	string s_skill,s_force,s_perform,s_base;
	int index;
        
    ::init();

	if( query("init") == 0 )
	{
		set("init", 1);

		index = random( sizeof( skill ) );

		s_skill = skill[ index ];
		s_force = force[ index ];
		s_perform = perform[ index ];
		s_base = base[ index ];
     
	    set_name(ob->query("g_name") + "����", ({ "hufa zhanglao", "hufa", "zhanglao"}));

	    set("gender", "����");
	    set("age", 20 + random(60));
	    set("long", "����" + ob->query("g_name") + "������ؽ�Ƹ������һλ���ָ��֡�\n"
	    	+ "��������̳�İ�ȫ��\n" );
	    set("combat_exp", ob->query("combat_exp"));
	    set("meitude", "peaceful");
	    set("str", 30 + random( 20 ) );
	    set("int", 30 + random( 20 ) );
	    set("con", 30 + random( 20 ) );
	    set("dex", 30 + random( 20 ) );
	    set("shen",0);
	    set("max_qi", 10000);
	    set("max_jing", 3000);
	    set("max_neili", 6000 + ob->query("combat_exp")/500 );
	    set("eff_jingli",3000);
	    set("neili", 6000 + ob->query("combat_exp")/500 );
	    set_skill(s_skill, lvl );
	    set_skill(s_force, lvl );
	    set_skill(s_base, lvl);
	    set_skill("dodge", lvl);
	    set_skill("force", lvl);
	    set_skill("parry", lvl);
	    set_skill("tiyunzong", lvl);

	    map_skill("force", s_force);
	    map_skill("dodge", "tiyunzong");
	    map_skill("parry", s_skill);
	    map_skill(s_base, s_skill);
	    prepare_skill(s_base, s_skill);
	
		set("chat_chance_combat", 50);
		set("chat_msg_combat", ({
			(: perform_action, s_base + "." + s_perform :)
		}) );

	    setup();
	    carry_object(ARMOR_D("cloth"))->wear();
    }
    
        
    if( interactive(ob1 = this_player()) )
    {
        remove_call_out("greeting");
        call_out("greeting", 0, ob1);
    }
}

void greeting(object ob)
{
    object me = this_object();
    object ob2 = environment();
        
    if (!ob || !present(ob, environment()) )
        return;

	if( interactive(ob) && ob->query("g_name")+ob->query("g_type")==ob2->query("g_name") )
		return;
		
	if( userp(ob)&& ob->is_fighting() && ob->query("g_name")+ob->query("g_type")!=ob2->query("g_name"))
	// add userp by Looklove ��������hufa do job //
	{
		say( HIR"�󵨿�ͽ���������Ұ���̳�����Ұ�����У�\n"NOR );
		me->kill_ob(ob);
		return;
	}

	call_out("greeting",1,ob);

    return;
}



string ask_rob()
{
	object me = this_player();
	object env = environment( me );
	
	if( me->query("g_name") + me->query("g_type" ) != env->query("g_name") )
	{
        return RANK_D->query_respect(me) + 
           "�ͱ��������������˻���֪�Ӻ�̸��";
	}
	
	if( me->query("g_level") > 3 )
	{
        return RANK_D->query_respect(me) + 
           "���д��ģ��κ��ڰ��е�Ӱ������������";
	}
	
	return 0;	
}
