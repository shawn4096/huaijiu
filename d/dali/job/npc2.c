//by cool 98.6.1
#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;
#include "skill.h";


string *first_name = ({ "��","Ǯ","��","��","��","��","֣","��","��","��","��","��","��","��", }); 
string *name_words = ({ "һ","��","��","��","��","��","��","��","��","ʮ", });
string *color_title = ({"��ɱ��ɱ��","��ɷ��ɱ��",});
string *k_weapon = ({"sword","blade","staff","whip","gun",});

void create()
{
	string name,weapon;

	name = first_name[random(sizeof(first_name))];
	name += name_words[random(sizeof(name_words))]; 
        weapon = k_weapon[random(sizeof(k_weapon))];

	set_name(name, ({ "sha shou", "shashou", "killer" }));
	set("title", color_title[random(sizeof(color_title))]);
	set("gender", "����");
	set("long", "��������ɫ��װ����������һ��ڲ���ֻ¶��һ˫�۾����������䡣\n");
	set("age", random(20)+25);      
	set("str", 20);
	set("int",20);  
	set("con",20);     
	set("dex",20);
	set("combat_exp", 100000);
        set("shen_type", -1);
        set("attitude", "friendly");
	set("max_qi",1200);
        set("max_jing",1200);
        set("neili",1000);
        set("eff_jingli", 1200);
        set("max_neili",1000);

	set_skill("force", 100); 
	set_skill("dodge", 100);
	set_skill("parry", 100);

	setup();  
	add_money("silver", random(40)+10);

	carry_object("/d/dali/obj/blackcloth")->wear();

}
#include "killer2.c"
