//cool 98.2.17

inherit NPC;
inherit F_MASTER;

string ask_me_wan();
string ask_me_dan();

object ob = this_object();


void create()
{
	set_name("������ʦ", ({
		"liaoming chanshi",
		"liaoming",
		"chanshi",
	}));
	set("long",
		"����һλ������ݵ�����ɮ�ˣ����۲�����׳���� \n"
              "һϮ�Ҳ�������ģ�����տտ�����ƺ���һ�����ա�\n"
	);


 set("nickname", "��������");
        set("gender", "����");
        set("attitude", "friendly");
        set("class", "bonze");
        set("age", 45);
        set("str", 23);
        set("int", 23);
        set("con", 23);
        set("dex", 25);
        set("max_qi", 1400);
        set("max_jing", 1300);
        set("neili", 1800);
        set("max_neili", 180);
        set("jiali", 70);
        set("combat_exp", 800000);
        set("shen", 8000);

	set_skill("force", 100);
        set_skill("qiantian-yiyang", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("tianlong-xiang", 100);
        set_skill("finger", 100);
        set_skill("sword", 100);
        set_skill("strike", 100);
        set_skill("qingyan-zhang", 100);
        set_skill("yiyang-zhi", 100);
        set_skill("buddhism", 100);
        set_skill("literate", 90);
        map_skill("strike", "qingyan-zhang");
        map_skill("force", "qiantian-yiyang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "yiyang-zhi");
        map_skill("finger",  "yiyang-zhi");
        prepare_skill("finger", "yiyang-zhi");
        create_family("������", 14, "����");    

//

	set("inquiry", ([
//         "ѩ¶��" :    (: ask_me_wan :),
//        "������" :    (: ask_me_dan :),
 		"ҩ" :  "�����鵤��ҩ���٣��������ľ�����������ѩ¶��",
	]));

	set("wan_count",2+random(2));
	set("dan_count",2+random(2));

       setup();
        carry_object("/d/tls/obj/jiasha1")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();

}

string ask_me_dan()
{
	mapping fam; 
        object ob, me;
                  me = this_player();
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";

  if ( (int)this_player()->query_condition("medicine" ) > 0 )
		return RANK_D->query_respect(this_player()) + 
		"���ǲ��ǸճԹ�ҩ����ô����Ҫ�ˣ� ��ҩ����к����ˣ�����ʱ�������ɡ�";

      if ( (int)this_player()->query("max_neili" ) < 300)
		return RANK_D->query_respect(this_player()) + 
		"������������ҩ�����к����ˣ�����ʱ�������ɡ�";

  if (  present("tianlong dan", this_player()) || present("xuelu wan", this_player())  )
		return RANK_D->query_respect(this_player()) + 
		"���������ϲ����п�ҩ������ô����Ҫ�ˣ� ����̰�����У�";
         if ((int)me->query("max_neili") >= (int)me->query_skill("force")*10)
return RANK_D->query_respect(this_player()) + "��ô�����ҩ�أ����书�Ѿ�������ȥ���������Ϊ�ɡ�";
	if (query("dan_count") < 1) return "�Բ����������Ѿ�������Ҫ���ˡ�";

         ob = new("/clone/medicine/tianlong-dan");
	ob->move(this_player());

	message_vision("$N���һ����������\n",this_player());
	return "�ðɣ��˵���֮���ף����������кô�����ҪС���ղغ��ˡ�";

}

string ask_me_wan()
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";

        if ( (int)this_player()->query_condition("bonze_drug" ) > 0 )
		return RANK_D->query_respect(this_player()) + 
		"���ǲ��ǸճԹ�ҩ����ô����Ҫ�ˣ� ��ҩ����к����ˣ�����ʱ�������ɡ�";

        if ( (int)this_player()->query("eff_jingli" ) < 200)
		return RANK_D->query_respect(this_player()) + 
		"������������ҩ����к����ˣ�����ʱ�������ɡ�";

	if ( present("tianlong dan", this_player())|| present("xuelu wan", this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"���������ϲ����п�ҩ������ô����Ҫ�ˣ� ����̰�����У�";
	if (query("wan_count") < 1) return "�Բ���ѩ¶���Ѿ�������";

	ob = new(__DIR__"obj/xuelu-wan");
	ob->move(this_player());

//	add("wan_count", -1);

	message_vision("$N���һ��ѩ¶�衣\n",this_player());
	return "�ðɣ���ҩ���������ƶ��ɣ�ϰ��֮�˷�֮���кô�����ҪС���ղء�";

}
#include "liao.h";

