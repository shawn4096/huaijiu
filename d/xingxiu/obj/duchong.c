// caiji@SJ
// 8/15/2000

inherit NPC;

#include <ansi.h>
//void checkfight();
//void check_position(int count);
//void display();
int do_copy(object target);

string *first_name = ({ RED+"深红色","黑色",GRN+"深绿色",YEL+"土黄色",BLU+"深蓝色",MAG+"浅紫色",CYN+"蓝绿色",WHT+"浅灰色",
HIR+"红色",HIG+"绿色",HIY+"黄色",HIB+"蓝色",HIM+"粉红色",HIC+"天青色",HIW+"白色",}); 
string *first_name_id = ({ "shenhong","hei","shenlv","tuhuang","shenlan","qianzi","lanlv","qianhui",
"hong","lv","huang","lan","fenhong","tianqing","bai",});

string *med_words = ({ "小","短","大","长", });
string *med_words_id = ({ "xiao","duan","da","chang",});

string *name_words = ({ "蜈蚣"+NOR,"蝎子"+NOR,"蜘蛛"+NOR,"沙虫"+NOR, });
string *name_words_id = ({ "wugong","xiezi","zhizhu","shachong",});

void create()
{
       
       int i, j, k;
       string name,name_word,med_name_word="";
       i = random(sizeof(first_name));
       name = first_name[i];

       if( random(10) > 5 ){
               k = random(sizeof(med_words));
               name += med_words[k];
               med_name_word = med_words_id[k];
       }
       
       j = random(sizeof(name_words));
       name += name_words[j]; 
       name_word = name_words_id[j];

        set_name(name, ({ first_name_id[i]+med_name_word+" "+name_word, name_word,"du chong"}) );
        set("race", "野兽");
        set("age", 10);
        set("long", "一只"+name+"，是星宿海附近常见的毒虫。\n");
        set("poison_damage",1+j+k+i/2);
        set("attitude", "peaceful");
        
        set("limbs", ({ "头部", "身体", "前爪", "后爪","前腿","後腿", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set("max_qi", 300);
        set("max_jing", 100);
        set("eff_jingli", 100);

        set("combat_exp", 1200);
        set("no_quest",1);
        set("no_ansuan",1);
        set("chat_chance", 10);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
                name+"在原地游来游去。\n",
                name+"游过来，在你的腿边爬来爬去。\n",
                name+"向着你，慢慢爬了过来。\n",
                }) );
        
    set_temp("apply/attack", 5);
    set_temp("apply/defense", 10);
    set_temp("apply/damage", 5);
    set_temp("apply/armor", 5);

        setup();
	if (clonep())
		call_out("dest", 180);
}

void dest()
{
	object me = this_object();

	message_vision ("\n$N向后一缩，钻进树丛不见了。\n",me);
        destruct (me);
}

int kill_ob(object victim) {
	object me=this_object();
	if(me->query("killing") && me->query("killing")!=victim){		
	message_vision ("\n$N向后一缩，钻进树丛不见了。\n",me);
        destruct (me);
        return 0;
        }else {
   command("bite "+victim->query("id"));
   do_copy(victim);
   me->set("killing",victim);
   return ::kill_ob(victim);
}
}

int do_copy(object target)
{
        object me,ob; 
        int exp;

        me = this_object();
        ob = target;

        exp = ob->query("combat_exp") *(8+random(4))/10;

        me->set("max_qi", (int)ob->query("max_qi"));
        me->set("eff_qi", (int)ob->query("max_qi"));
        me->set("qi", (int)ob->query("max_qi"));    
        me->set("max_jing",(int)ob->query("max_jing"));
        me->set("eff_jing",(int)ob->query("max_jing"));
        me->set("jing",(int)ob->query("max_jing"));
        me->set("max_neili",(int)ob->query("max_neili") );
        me->set("neili",(int)ob->query("neili"));
        if( me->query("neili") < me->query("max_neili") )
                me->set("neili",(int)me->query("max_neili") );
        me->set("max_jingli",(int)ob->query("max_jingli"));
        me->set("eff_jingli",(int)ob->query("eff_jingli"));
        me->set("jingli",(int)ob->query("jingli"));
        if( me->query("jingli") < me->query("eff_jingli") )
                me->set("jingli",(int)me->query("eff_jingli") );        
        me->set("combat_exp",exp );     
        me->set_temp("apply/attack", (int)ob->query_temp("apply/attack")*(5+random(5))/10);
        me->set_temp("apply/defense", (int)ob->query_temp("apply/defense")*(5+random(5))/10);
        me->set_temp("apply/damage", (int)ob->query_temp("apply/damage")*(5+random(me->query("poison_damage"))/15));

        me->set("jiali",(int)target->query("jiali")/2);
}

void unconcious()
{
	string st1,st2;
  object ob;
  object me = this_object();
  object where = environment (me);
  object target=me->query_temp("last_damage_from");
  
	if (objectp(target) && sscanf(me->query("id"),"%s %s", st1, st2) == 2) {
		ob = new (__DIR__+st2);
		ob->set("name",me->query("name"));
		ob->move(where);
		ob->set("cook/owner",target->query("id"));
		ob->set("cook/value",me->query("poison_damage"));
	}
	message_vision ("\n$N缩成一团，不再动了。\n",me,ob);
	destruct (me);
}

void die()
{
	unconcious();  
}
