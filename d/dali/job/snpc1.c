//by cool 98.6.1
#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;
#include "skill.h";
#define RNAME_D "/inherit/misc/r_name"

string *color_title = ({"��ɱ��ɱ��","��ɷ��ɱ��",});
string *k_weapon = ({"sword","blade","staff","whip","gun",});

void create()
{
	mapping name;
	int sex = random(3);
	string weapon;

        name = RNAME_D->get_random_name(sex);
        weapon = k_weapon[random(sizeof(k_weapon))];

	set_name(name["name"], name["id"]);
        set("title", color_title[random(sizeof(color_title))]);
	set("gender", sex?"����":"Ů��");
	set("long", "��������ɫ��װ����������һ��ڲ���ֻ¶��һ˫�۾����������䡣\n");
	set("age", random(20)+25);      
	set("str", 25);
       	set("int",20);  
       	set("con",20);     
       	set("dex",20);
       	set("combat_exp", 100000);
	set("no_quest", 1);   
        set("shen_type", -1);
        set("attitude", "friendly");
	set("max_qi",1200);
        set("max_jing",1200);
        set("neili",1000);
        set("max_neili",1000);
	set("score", 100);

      	
	set_skill("force", 100); 
	set_skill("dodge", 100);
	set_skill("parry", 100);

        setup();  
//	if (!random(3))
//		add_money("gold", random(5)+1);

carry_object("/d/dali/obj/blackcloth")->wear();

}
#include "stealer1.c"
