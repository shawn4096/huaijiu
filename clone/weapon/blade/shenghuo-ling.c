// shenghuo-ling.c

#include <weapon.h>
inherit F_BLADE;
inherit F_EQUIP;
inherit COMBINED_ITEM;
inherit F_UNIQUE;

void set_amount(int v)
{
        object owner = environment();
        if (v >= 0) {
                set("weapon_prop/damage", v * (int)query("base_damage"));
                set("rigidity", v * query("base_rigidity"));
                if (query("equipped") && objectp(owner)) {
                        owner->set_temp("apply/damage", query("weapon_prop/damage") );
                }
        }
        ::set_amount(v);
}

void add_amount(int v) { set_amount((int)query_amount()+v); }


void create()
{
        set_name("圣火令", ({ "shenghuo ling","shenghuo","ling" }));
        set_weight(9000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是一柄两尺来长的令牌，质地怪异，极是坚硬，是明教的圣物。\n"
                        "令中隐隐有火陷飞腾，似透明，非透明，上面刻有不少的波斯文字。\n");
                set("value", 10);
                set("base_unit", "块");
                set("base_weight", 9000);
                set("base_damage", 50);
                set("base_rigidity", 5);
                set("material", "steel");
                set("rigidity", 10);
                set("unique", 6);
                set("weapon_prop/parry", 1);
                set("weapon_prop/dodge", 1);
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回腰间。\n");                
                set("treasure",1);
        }    
        set_amount(1);           
        init_blade(50);
        setup();
}

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}
int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        int qklevel; 
        int neili_lost;
        if (!(arg=="shenghuo ling" ||arg=="ling"))
                return 0;
        if (where->query("pigging")){
                write("你还是专心拱猪吧！\n");
                return 1;
        }
        if (me->is_busy()) {
                write("你现在正忙着呢。\n");
                return 1;
        }

        if( me->is_fighting() ) {
                write("你无法在战斗中专心下来研读新知！\n");
                return 1;
        }

        if (!id(arg)) { 
                write("你要读什么？\n");
                return 1;
        }
       
        if(me->query_skill("literate", 1) < 80){
                write("你还不能读懂令上面的文字，先学点文化(literate)吧。\n");
                return 1;
        }
        if(me->query_int()<33){
                write("你对着圣火令上的波斯文字认真的研究，但终是不能明白其意。\n");
                return 1;
        }
        if(me->query_skill("shenghuo-shengong",1) < 100){
                write("你的圣火神功火侯太浅，不能领会令上的高深武功。n");
                return 1;
        }
        if(me->query_skill("shenghuo-lingfa",1)<101){
                write("你的圣火令法还太低，不能从中学到什么。\n");
                return 1;
        }
        message("vision", me->name() + "正在研读圣火令。\n", environment(me), me);
         
        if((int)me->query("jing") < 15 ) {
                write("你现在过于疲倦，无法专心下来研读新知。\n");
                return 1;
        }
        
        if( (int)me->query("neili") < neili_lost) {
                write("你内力不够，无法钻研这么高深的武功。\n");
                return 1;
        }

        qklevel = me->query_skill("shenghuo-lingfa", 1);
        if( (int)me->query("combat_exp") < (int)qklevel*qklevel*qklevel/10 ) {
                write("你的实战经验不足，再怎么读也没用。\n");
                return 1;
        }
        if (me->query_skill("shenghuo-lingfa",1)>120){
                write("你已不能从这上面学到任何东西了。\n");
                return 1;
        }
         neili_lost=(int)(me->query_skill("shenghuo-shengong",1)/10);
        me->receive_damage("jing", 15);
        me->set("neili",(int)me->query("neili")-neili_lost);
        me->improve_skill("shenghuo-lingfa", (int)me->query_skill("literate", 1)/3+1);
       
        write("你正在研习圣火令上的武功，似乎有点心得。\n");
        return 1;
}

int wield() 
{
        object me = environment();

/*if (living(me) && !me->query_skill("shenghuo-lingfa", 1)){
                message_vision("$N拿出"+name()+"看看了，却搞不懂怎么使用这个东西。\n", me);
                return 0;
}*/
        if( query_amount() > 2 ){
                message_vision("$N拿出"+name()+"看看了，却搞不懂怎么同时使用它。\n", me);
                return 0;
        }    
        if (query_amount() > 1){
        	if (me->query_skill("shenghuo-lingfa", 1) < 200 || me->query_int() < 38){
                	message_vision("$N拿出"+name()+"看看了，却搞不懂怎么用它。\n", me);
                	return 0;
                }
        }
	if(!query("weapon_prop/damage")) return 0;
        return ::wield();
}
