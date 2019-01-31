// cateran.c
// Modify By River@SJ
#include <ansi.h>
inherit NPC;
void check();
string *title = ({
"ÌìºÓ°ï°ïÖÚ","³¤¾¨µº°ïÖÚ","ÉñÅ©°ï°ïÖÚ","¾Þ¾¨°ï°ïÖÚ","º£É³ÅÉ°ïÖÚ","ÇàÖñ°ï°ïÖÚ",
"ÁúÓÎ°ï°ïÖÚ","½ðÁú°ï°ïÖÚ","Û¶Ñô°ï°ïÖÚ","¶ñ»¢¹µ°ïÖÚ","Ç§Áø×¯°ïÖÚ" });
void create()
{
	set_name("½Ù·Ë", ({ "jie fei", "cateran", "fei" }));
        set("title", HIW+title[random(sizeof(title))]+NOR);
        set("gender", "ÄÐÐÔ");
        set("age", 27);
        set("int", 22);
        set("per", 10);
        set("long","Õâ¸öÀ¹Â·µÄ½Ù·ËÊÇ"+this_object()->query("title")+"£¬ËûÂúÁ³ÉË°Ì£¬»¢±³ÐÜÑü£¬Ò»Á³Ð×ºÝ¶ø°ÔµÀµÄÑù×Ó¡£\n");

        set("vendetta/authority",1);
        set("attitude", "heroism");
        set("bellicosity", 1500 );

        set_skill("unarmed", 20);
        set("combat_exp", 10000);
        set_temp("no_return",1);
	set_temp("apply/unarmed", 900);
        set("chat_chance", 100);
        set("chat_msg", ({
             (: check :),
        }));
	set("no_get", 1);

        set("chat_chance_combat", 3);
        set("chat_msg_combat", ({
              "½Ù·Ë¸ßº°£º½ÐÄãÈË²ÆÁ½¿Õ¡£",
        }));

        setup();
        carry_object("/clone/armor/cloth")->wear();
}

void init()
{
        object cart,me=this_player();

	::init();
        if((cart=query_temp("target",1))
         && me->query_temp("protecting",1) 
         && me->query_temp("protecting",1)==cart){
            kill_ob(me);
            me->kill_ob(this_object());
        }      
}

void check()
{
        object* obj;
        object cart,ob=this_object();
        int i;
        obj = all_inventory(environment(ob));
        if(objectp(cart=query_temp("target",1))){
            for(i=0; i<sizeof(obj); i++){
                if(userp(obj[i]) 
                 && obj[i]->query_temp("protecting",1) 
                 && obj[i]->query_temp("protecting",1)==cart){
                   obj[i]->kill_ob(ob);
                   kill_ob(obj[i]);
                }
            }
        }
}
