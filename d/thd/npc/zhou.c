// Modify By River@SJ about jieyi and hubo
// Modify by Darken for taohua quest 2k
// Modify By River@Sj for jiuyin quest
inherit NPC;
#include <skill.h> 
#include <ansi.h>
#include "question.h"

int ask_jieyi();
int do_answer(string arg);
int questions(object me);
int ask_jiuyin();
int ask_hubo();
int do_fangyuan();
int do_learn(string arg);
int ask_story();
int ask_skill();
int ask_story2();
void waiting(object ob);
void create()
{
        set_name("�ܲ�ͨ", ({ "zhou botong", "zhou", "botong" }) );
        set("nickname", "����ͯ");
        set("long", 
                "����ͷ������ֱ�����أ���ü���룬������Ͷ�������ס�ˡ�\n"
                "���뷢��Ȼ����δȫ�ף�ֻ�ǲ�֪�ж����겻�꣬����Ұ��һ��ë���׵��������ˡ�\n"
                "���ľ�ֹ���红ͯһ����\n");
        set("gender", "����" );
        set("age", 48);
        set("attitude", "peaceful");
        set("apprentice", 1);
        set("str",28);
        set("int",25);
        set("con",30);
        set("dex",29);
        set("unique", 1);
        set("per", 20);
        set("no_get", "�ܲ�ͨ�������̫���ˡ�\n");
        
        set("max_qi", 5000);
        set("max_jing", 3500);
        set("neili", 8000);
        set("jiali", 100);
        set("combat_exp", 2200000);
        set("eff_jingli",3000);
        set("double_attack", 1);
        set("score", 50000);

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :)
        }));

        set_skill("force", 280);
        set_skill("xiantian-gong", 280);
        set_skill("dodge", 290);
        set_skill("tiyunzong", 290);
        set_skill("cuff", 300);
        set_skill("kongming-quan", 300);
        set_skill("parry", 280);
        set_skill("sword", 280);
        set_skill("quanzhen-jianfa", 280);
        set_skill("taoism", 150);
        set_skill("literate", 130);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "kongming-quan");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("parry", "quanzhen-jianfa");
        prepare_skill("cuff", "kongming-quan");

        set("rank_info/respect", "����ͯ");
        set("shen_type", 1);
        create_family("ȫ���", 2, "����");
        set("class", "taoist");

        set("inquiry", ([
                "name": "�����ܲ�ͨ�ͺ��ˡ�",
                "rumors": "�ұ��Ǹ�����а��������ʮ���꣬ÿ�����һ���������ͷ���",
                "here": "�������һ����������Ǹ�С������������������ģ�������������ܲ�����ȫ�ˡ�",
                "��а": "�ǻ�ҩʦ����޳ܵļһƭ���ҵľ�....ȥ����",
                "��ҩʦ": "����޳ܵļһƭ���ҵľ�....ȥ����",
                "����ͨ": "�ҵ�ʦ���������书��ߵģ���һ�λ�ɽ�۽�ʱ����Ϊ��һ���֡�",
                "������": "�ҵ�ʦ���������书��ߵģ���һ�λ�ɽ�۽�ʱ����Ϊ��һ���֡�",
                "�ܲ�ͨ": "������ʲô����",
                "����": "���Ż���ԧ��֯����˫��....",
                "����": "���Ż���ԧ��֯����˫��....",
                "�λ�ү": "����ͯ���¶Բ�������û���ټ����ˡ�",
                "������": "����ͯ���¶Բ�������û���ټ����ˡ�",
                "�ϵ�": "����ͯ���¶Բ�������û���ټ����ˡ�",
                "����ͯ": "�Ҿ��ǰ���������ʲô����",
                "����ȭ": "����ȭ����ʮ��·���ھ��ǣ��������ɡ���ͨ���Ρ�������Ū��ͯӹ���档",
                "kongming-quan": "����ȭ����ʮ��·���ھ��ǣ��������ɡ���ͨ���Ρ�������Ū��ͯӹ���档",
                "����": "�Ǽ�����ǰ������������Ǹ�С������",
                "����": "�����ҵĽ����ֵܣ�����Ȼɵ���ĳ����á�",
                "����": "˵����Ҳ�����������ң�������һ��Ǹ�����������",
                "jpei": "˵����Ҳ�����������ң�������һ��Ǹ�����������",
                "�һ���": "��������һ����������Ǹ�С������������������ģ�������������ܲ�����ȫ�ˡ�",
                "��": "��Ҫ������",
                "fang": "��Ҫ������",
                "Բ": "ԲҪ��Բ��",
                "yuan": "ԲҪ��Բ��",
                "�����澭": "��������ر��ˡ�",
                "˫�ֻ���": (: ask_hubo() :),
                "���һ���": (: ask_hubo() :),
                "����":  (: ask_jieyi() :),
                "���":  (: ask_jieyi() :),
                "����":  (: ask_story() :),
                "��������":  (: ask_story2() :),
                "�书":  "��������ر��ˡ�",
                "����":  "��������ر��ˡ�",
        ]));
        setup();
        carry_object("/d/wudang/obj/white-robe")->wear();
}

void init()
{
        object ob = this_player();
        add_action("do_fangyuan","fangyuan");
        add_action("do_draw","draw");
        add_action("do_draw","hua");
        add_action("do_answer","answer");
        add_action("do_learn","learn");
        add_action("do_learn","xue");
        ::init();
        if (ob->query("family/family_name") == "ȫ���") {
                command("angry " + ob->query("id"));
                command("say ��ô�㵽����������ң��������Ҿ�ȥ�ʹ���˵��������ƨ�ɡ�");
        }
        if (ob->query("jiuyin-sj/failed") >= 3 && !ob->query("zhou/jieyi")) {
                command("slogan " + ob->query("id"));
                message_vision(CYN"�ܲ�ͨһ�Ű�$N�߳�ȥ��������$N�����ˡ�\n"NOR,ob);
                ob->move("/d/thd/dongkou");
        }
}

void kill_ob(object me)
{
        command("chat* crazy " + me->query("id"));
        ::kill_ob(me);
}

void unconcious()
{
        command("chat* ̾��������ͯ������Ҫ�����ˣ�������������ֻ���ܣ���Щ��ͷ���޳���һ���Ƶ�Ī�������ɫ��䡣");
        ::unconcious();
}


int ask_story()
{
        object me = this_player();
        string msg;
        msg = CYN"�ܲ�ͨ����$NҪ�������£���ʱ�˸߲��ҡ�\n"NOR;
        msg+= CYN"�ܲ�ͨ��ʼ��������澭�ͻ��ѵĹ��¡�\n"NOR;
        msg+= CYN"�ܲ�ͨ��$N���ʺ����������������˵�ˡ�\n"NOR;
        message_vision(msg, me);
        me->set_temp("thd/story",1);
        return 1;
}

int ask_story2()
{
        object me = this_player();
        string msg;
        if (me->query_temp("thd/story") == 1){
                msg = CYN"�ܲ�ͨһ��$N���������������ֿ�ĭ��ɵ�˵������\n";
                msg+= CYN"�ܲ�ͨ�����ֿ�ʼ��$N˵������ȫ��̵Ĺ��¡�\n";
                msg+= CYN"$N���ţ�Ҳѧ����Щȫ���������Ƥë��\n"NOR;
                msg+= HIW"�ܲ�ͨ˵����£������ĵ��ʵ������ֵܣ���ʲô������书ô��\n"NOR;
                message_vision(msg, me);
                me->set_temp("thd/story",2);
                return 1;
        }
        message_vision(CYN"�ܲ�ͨ��ֵ��ʵ�����ʲô������������\n"NOR, me);
        return 1;
}

int ask_jieyi()
{
        object ob=this_player();
        if (ob->query("zhou/jieyi")) {
                command("? " + ob->query("id"));
                command("say �������ǽ�ݹ�����");
                return 1;
        }
        if ( ob->query("combat_exp") < 100000){
                command("shake "+ ob->query("id"));
                command("say ��λ"+RANK_D->query_respect(ob)+"�������ʵ��̫����ˣ��ҿ�û��Ȥ�����ݡ�");
                return 1;
        }
        if (!ob->query_temp("jieyi")){
                command("hmm");
                command("say ��˭������û��Ȥ�����ݣ�");
                return 1;
        }
        if (ob->query("age") > 300){
                command("shake");
                command("say �����������ְ��������ݣ�û��˼��û��˼��");
                return 1;
        }

/*      if (ob->query("gender") != "����" && ob->query("gender") != "Ů��") {
                if (ob->query("age") > 48) 
                        command("say �ұ���Ҳ�������ݣ����ǲ�֪���ֵ���ƻ��ǽ����ƣ�");
                else
                        command("say �ұ���Ҳ�������ݣ����ǲ�֪���ֵ���ƻ���������ƣ�");
                command("laugh");
                ob->add("zhou/fail", 1);
                log_file("quest/ZHOU",sprintf("%s %s(%s)�����ܲ�ͨ��ݣ�ʧ��%s�Ρ�\n",
                       ctime(time())[4..19], ob->name(1), capitalize(getuid(ob)),chinese_number(ob->query("zhou/fail")) ));
                return 1;
        }
        if ( ob->query("class") =="bonze" || ob->query("class") == "huanxi"){
                command("monk "+ ob->query("id"));
                command("say "+RANK_D->query_respect(ob)+"������ͯ�ҿ�û����Ȥ�����ݡ�");
                ob->add("zhou/fail", 1);
                log_file("quest/ZHOU",sprintf("%s %s(%s)�����ܲ�ͨ��ݣ�ʧ��%s�Ρ�\n",
                       ctime(time())[4..19], ob->name(1), capitalize(getuid(ob)),chinese_number(ob->query("zhou/fail")) ));
                return 1;
        }*/

        if ( ob->query("int") > 25) {
                command("shake");
                command("say ������˹��龫������׼����ʲô�����ء�");
                ob->delete_temp("jieyi");
                log_file("quest/ZHOU",sprintf("%s %s(%s)�����ܲ�ͨ��ݣ�ʧ�ܡ�\n",
                       ctime(time())[4..19], ob->name(1), capitalize(getuid(ob)) ));
                return 1;
        }

        if ((int)ob->query("shen") <= -1) {
                command("shake");
                command("say ����Ȼ������㣬��ʦ��̻岻����������а֮������Ҫ����ġ�");
                ob->delete_temp("jieyi");
                log_file("quest/ZHOU",sprintf("%s %s(%s)�����ܲ�ͨ��ݣ�ʧ�ܡ�\n",
                       ctime(time())[4..19], ob->name(1), capitalize(getuid(ob)) ));
                return 1;
        }

        if (random(ob->query("kar")) < 20 && random(ob->query_int(1)) < 30){
                command("shake");
                command("say ������û�пգ�Ҫ�������������棿");
                ob->delete_temp("jieyi");
                log_file("quest/ZHOU",sprintf("%s %s(%s)�����ܲ�ͨ��ݣ�ʧ�ܡ�\n",
                       ctime(time())[4..19], ob->name(1), capitalize(getuid(ob)) ));
                return 1;
        }
        command("nod " + ob->query("id"));
        if (ob->query("gender") == "����") {
                command("say �ðɣ����Ҿͽ��Ϊ�ֵܰɡ�");
        }
        else if (ob->query("gender") == "Ů��") {
                if (ob->query("age") > 48) 
                        command("say �ðɣ����Ҿͽ��Ϊ��ܰɡ�");
                else
                        command("say �ðɣ����Ҿͽ��Ϊ���ðɡ�");
        }
        message_vision("�ܲ�ͨ��$N�����������˵����������ͯ�ܲ�ͨ��������" + ob->name() +"���������պ��и��������ѹ�����\n"+
                       "����Υ�����ģ������书ȫʧ����С��СèҲ�򲻹�����\n", ob);
        log_file("quest/ZHOU",sprintf("%s %s(%s)���ɹ����ܲ�ͨ��ݡ�\n",
            ctime(time())[4..19], ob->name(1),capitalize(getuid(ob)) ));
        ob->delete_temp("jieyi");
        ob->set("zhou/jieyi", 1);
        return 1;
}

int ask_jiuyin()
{
        object ob=this_player();
        object zhou = this_object();
        object book;
        
        if(present("jiuyinzhenjing shangjuan", ob)) {
                command("faint");
                command("say �㲻������ô��");
                return 1;
        }
        if( zhou->is_busy() || zhou->is_fighting()){
                command("hmm");
                command("say ��û��������æ��ô��");
                return 1;
        }
        if( ob->query("jiuyin-sj/failed") >= 3){
                command("say ����æ���ء�");
                return 1;
        }
        if (ob->query("jiuyin/passed")){
                book = unew("/d/thd/obj/jiuyin-book1");
                if(!clonep(book)){
                   command("pat");
                   command("say ������û�пգ��������澭�Ͼ���Ȼ�����Ҫ�ɡ�");
                   return 1;
                }
                if(clonep(book) && book->violate_unique()){
                   destruct(book);
                   command("pat");
                   command("say ������û�пգ��������澭�Ͼ���Ȼ�����Ҫ�ɡ�");
                   return 1;
                }                 
                command("consider");
                command("say ��Ҫ�ٳ�һ�ݣ�");
                message_vision(HIW"$N���³�¼��һ�ݾ����澭���Ͼ�\n"NOR,ob);
                book->set("owner", ob->query("id"));
                book->move(ob);
                return 1;
        }
        if (ob->query_temp("jyquest") != 3) {
                command("? " + ob->query("id"));
                return 1;
        }
        command("say �����澭���Ǹ���������ʦ��ģ����Ǹ�����а��������ƭ��ȥ��");
        command("say �������Ÿ��������Ͼ��ȱ��ȫ���¾��ֱ����Լ�ͽ��͵�ˣ�����ͽб�Ӧ��");
        command("laugh zhou");
        ob->set_temp("jyquest", 4);
        command("say ���������������������ѵ��и������ң���������ˡ�");
        message_vision(HIY"�ܲ�ͨ����$N˵�������ԹԵ�����˵���°ɡ���\n"NOR,ob);
        command("grin");
        ob->move("/d/thd/neidong");
        zhou->move("/d/thd/neidong");
        call_out("waiting", 120, ob);
        return 1;
}

int ask_skill()
{
        object me=this_player();
        object ob = this_object();
        object book;
        object* ppl;
        int i, j =0;
        
        if (me->query_temp("jyquest") != 5) {
                command("? " + ob->query("id"));
                return 1;
        }
        command("hehe zhou");
        command("say ��Щ���������Լ��Ĵ������������ĺܰ���");
        message_vision(CYN"�ܲ�ͨȴֻ�Ǹ���$N���ʩչ����ȫ��������$N����\n"NOR,me);
        i = sizeof(ppl);
        while(i--) {
            if (userp(ppl[i]) && !wizardp(ppl[i]) && ppl[i]->query("jiuyin/passed"))
            j++;
        } 
        if( me->query("combat_exp") > 1000000 
          && random(me->query("int")+ me->query_skill("literate", 1)/10) > 35 
          && random(me->query("kar")) > 25 
          && random(me->query("pur")) > 25
          && me->query("jiuyin-sj/failed") < 3 
          && j < 1){ 
           message_vision(HIW"\n�ܲ�ͨ��$N��ϰ�����ᣬͻȻ������Ц������\n"NOR,me);
           command("haha");
           command("laugh");
           command("say ��Щ�����书����ô�����Լ��Ĺ����Ǿ��Ǿ����澭����");
           command("say ���������㿴�����⹦���������������Ҳ�Ŀ�ˡ�");
           book=unew("/d/thd/obj/jiuyin-book1");
           if( !me->query("jiuyin/passed"))
           log_file("quest/jiuyin",sprintf("%s %s(%s)ʧ��%s�κ󣬴��ܲ�ͨ���õ������澭�ϲ��ֳ�����\n",
            ctime(time())[4..19], me->name(1),capitalize(getuid(me)),chinese_number(me->query("jiuyin/failed")) ));
           me->delete_temp("jyquest");
           me->set("jiuyin/passed",1);
           if(!clonep(book)){
               command("hungry");
               command("say ���ˣ��������ˣ����Ӷ����ˣ���Ҫ�Է�ȥ�ˡ�");
               return 1;
           }
           if(clonep(book) && book->violate_unique()){
               destruct(book);
               command("hungry");
               command("say ���ˣ��������ˣ����Ӷ����ˣ���Ҫ�Է�ȥ�ˡ�");
               return 1;
           }                 
           command("say �������Ѿ�ѧ���ˣ�������澭�Ͼ����㳭¼һ��ȥ�ɡ�");
           message_vision(HIW"$N�������澭���Ͼ�С�ĵĳ�¼������\n"NOR,me);
           book->set("owner", me->query("id"));
           book->move(me);
           return 1;
        }
        message_vision(CYN"$N������ô��ϰ�����޷��ɹ���\n"NOR,me);
        command("sigh");
        command("say ��������书�����ű���ѧ�˰ɡ�");
        command("disapp");
        me->add("jiuyin-sj/failed", 1);
        if(me->query("jiuyin-sj/failed")){
         if(me->query("jiuyin-sj/failed") < 3 )
        log_file("quest/jiuyin",sprintf("%s %s(%s)����ܲ�ͨ���õ������澭�ϲᣬʧ��%s�Ρ�\n",
          ctime(time())[4..19], me->name(1),capitalize(getuid(me)),chinese_number(me->query("jiuyin-sj/failed")) ));
         else 
        log_file("quest/jiuyin",sprintf("%s %s(%s)ʧ�����Σ��޷��ٴ��ܲ�ͨ���õ������澭�ϲᡣ\n",
          ctime(time())[4..19], me->name(1),capitalize(getuid(me))));
        }
        me->delete_temp("jyquest");
        return 1;
}

void waiting(object ob)
{
        if((ob->query_temp("thd/story")==2 )&&(ob->query_temp("jyquest")==4)&&(ob->query_temp("jiuyin/question")>3)){
                command("say ������������ô�ã�һ�������İɣ�");
                command("hmm");
                command("ah zhou");
                command("say �����ɣ��ҽ�������Ĺ���");
                command("grin");
                ob->set_temp("jyquest",5);
                ob->move("/d/thd/cave");
                this_object()->move("/d/thd/cave");
        } else
        {
                command("yawn");
                command("say ��������ֱ������ģ���ȥ����ȥ��");
                ob->delete_temp("jyquest");
                ob->add("jiuyin/failed", 1);
                ob->move("/d/thd/cave.c");
                destruct(this_object());
        }
}

int ask_hubo()
{
        object ob=this_player();
        int hubo,time;
        time = time()-ob->query("hb_time");
        if( ob->query("hb_time") && time < 86400 ) {
             tell_object(ob,HIG"�������ܲ�ͨ��"+CHINESE_D->chinese_time(86400-time)+"֮�ڲ��������㡣\n"NOR);
             return 1;
        }
        if(!ob->query("zhou/jieyi")){
                tell_object(ob,"�ܲ�ͨ�������㿴����֪����Щʲô���⡣\n");
                command("say ����˭������ôĪ�����������˫�ֻ������°���");
                return 1;
        }               
        if (ob->query("double_attack")) {
                command("? " + ob->query("id"));
                command("say �㲻���Ѿ�ѧ������");
                return 1;
        }
        if(!ob->query_temp("hubo")){
                command("shake " + ob->query("id"));
                command("say ��û��ʹ��С��֦������ܹ�����˫�ֻ���֮����");
                return 1;
        }
        
        hubo = ob->query_temp("zuoyou_hubo");
        ob->set("hb_time",time());
        if (hubo == 22) {
                command("say ��������һ�Σ�");
                return 1;
        }
        if (hubo == 1) {
                command("say ��������Ϳ����");
                return 1;
        }
        if (hubo > 1 && hubo <= 21) {
                command("say ��ô����������ɣ����������Ů����������͸��һ���Ķ�������ʮ�߰˸��ϣ��������Ź�������ʼ��ѧ���ᣡ");
                return 1;
        }
        if (ob->query_skill("force") < 100 || ob->query("max_neili") < 500 || ob->query("combat_exp") < 10000) {
                command("say �㻹���ȴ����ѧ������˵�ɡ�");
                return 1;
        }
        command("say ���Ź��������ڶ�������֮ʱ��������������˵�����ѵ�������˵����Ҳ����֮����\n"+
                "�е���һѧ��ᣬ�е���һ����Ҳѧ���ˣ�Խ�Ǵ�����Խ�ǲ��ɡ�");
        command("say �����������һ�Σ����ֻ���(fang)�����ֻ�Բ(yuan)��");
        ob->delete_temp("hubo");
        ob->set_temp("zuoyou_hubo", 1);
        return 1;
}

int do_fangyuan()
{
        object ob=this_player();
        int hubo;
        if (ob->is_busy() || ob->is_fighting()) return notify_fail("����æ���أ�\n");
        hubo = ob->query_temp("zuoyou_hubo");
        if (!hubo) return 0;
        if (hubo < 21) {
                message_vision("$N�������ʳָ�ڵ��ϻ��������������ķ����е���ԲȦ��ԲȦ���е��󷽿顣\n", ob);
                ob->add_temp("zuoyou_hubo", 1);
                return 1;
        }
        if (hubo == 21) {
                message_vision("$N�������ʳָ�ڵ��ϻ��������������ķ����е���ԲȦ��ԲȦ���е��󷽿顣\n", ob);
                command("haha " + ob->query("id"));
                command("say ��ô������һ�±�첻����");
                ob->add_temp("zuoyou_hubo", 1);
                return 1;
        }
        if (hubo == 22) {
                if ( random(10) > 4 ){
                    if( random(30) > 28 ){
                        message_vision("$N΢΢һЦ��������һ���ĵؿ���������������˫����ָ�����ֻ���һ�����飬���ֻ���һ��ԲȦ��\n"+
                                       "����������Բ�߻�Բ��\n", ob);
                        say("�ܲ�ͨ���һ�������˰��βŵ������ⶨ�������̥��ѧ���ı��죬�Ǳ��װ��ˡ���\n");
                        message_vision("�ܲ�ͨ����������������������ޱȵ��湦��һ���Զ����̸���$N��\n", ob);
                        ob->delete_temp("zuoyou_hubo");
                        log_file("quest/ZHOU",sprintf("%s %s(%s)�����ܲ�ͨ������˫�ֻ�����\n",
                                  ctime(time())[4..19], ob->name(1),capitalize(getuid(ob)) ));
                        ob->set("double_attack", 1);
                        ob->set("zhou/hubo", 1);
                        return 1;
                    }
                    else {
                        ob->delete_temp("zuoyou_hubo");
                        message_vision("$N���������ʳָ�ڵ��ϻ����������������Ծ��Ƿ����е���ԲȦ��ԲȦ���е��󷽿顣\n", ob);
                        write("������������ô�򵥡�\n");
                        log_file("quest/ZHOU",sprintf("%s %s(%s)����ܲ�ͨ������˫�ֻ�����ʧ�ܡ�\n",
                             ctime(time())[4..19], ob->name(1), capitalize(getuid(ob)) ));
                        return 1;
                    }
                }
                message_vision("$N���������ʳָ�ڵ��ϻ����������������Ծ��Ƿ����е���ԲȦ��ԲȦ���е��󷽿顣\n", ob);
                message_vision("$N���ڷ����Լ���һ����Ҳ���������Ź����ˡ�\n", ob);
                ob->delete_temp("zuoyou_hubo");
                log_file("quest/ZHOU",sprintf("%s %s(%s)����ܲ�ͨ������˫�ֻ�����ʧ�ܡ�\n",
                    ctime(time())[4..19], ob->name(1), capitalize(getuid(ob)) ));
                command("disapp " + ob->query("id"));
                return 1;
        }
        return 0;
}

int do_draw(string arg)
{
        object ob=this_player();

        if (!ob->query_temp("zuoyou_hubo")) return 0;
        if (arg == "fang" || arg == "��" || arg == "yuan" || arg == "Բ") return notify_fail("�ܲ�ͨŭ��������ͬʱ����Բ��\n");
        if (arg == "fang yuan" || arg == "��Բ") return do_fangyuan();
        return 0;
}


int accept_object(object who, object ob)
{
        if (ob->id("skin") && ob->query("material") == "paper") 
        {
                if ((who->query_temp("thd/onquest") == 7)&&(who->query_temp("thd/story")==2))
                {
                        message_vision(CYN"�ܲ�ͨ����Ƥ��ϸ�鿴�������Ǿ����澭��\n"NOR, who);
                        message_vision(CYN"��������ȥ������ҩʦ��ȴ���ܲ�ͨ��ס��\n"NOR, who);
                        command("say ����ȵ���˵����������ɣ�");
                        command("sing");                        
                        command("say �þ�û������������������������ɣ�");
                        command("hit " + who->query("id"));
                        call_out("finish",5, who);
                        return notify_fail("");
        } else {
                        command("? " + who->query("id"));
                        command("say ���������ʲô��\n");
                        return notify_fail("");
                }
        }
        else
        if (who->query_temp("jyquest")==2 && ob->id("fan he") && ob->query("material") == "wood")
        {
                command("ah " + who->query("id"));
                command("say �ǻ���а��СѾͷ�����æ�ͷ���ô��");
                message_vision(CYN"�ܲ�ͨ����$N�ش��Ѿ���ʼ��ʳ���������С�\n"NOR,who);
                message_vision(CYN"�ܲ�ͨ���꣬��Ц��һ�£��Ŷ�$N�ʵ�������֪����Թ���û�У���\n"NOR,who);
                who->set_temp("jyquest", 3);
                command("say ����а��Ҫ�ҵľ����澭�����ҹ���ʮ��������");
                command("sing3");
                return 1;
         }
        return 0;
}


int do_learn(string arg)
{
        object me=this_player();
        string skill, teacher, skill_name;
        object ob;
        int master_skill, my_skill, gin_cost, rand;

        if (me->is_busy())
                return 0;

        if(!arg || (sscanf(arg, "%s %s", teacher, skill)!=2 ))
                return 0;

        if (teacher != "zhou" && teacher != "botong")
                return 0;

        if( me->is_fighting() )
                return 0;

        if( !(ob = present(teacher, environment(me))) || !ob->is_character()) {
                write("��Ҫ��˭��̣�\n");
                return 1;
        }

        if( !living(ob) ) {
                write("��....����Ȱ�" + ob->name() + "Ū����˵��\n");
                return 1;
        }

        if( !me->query("zhou/jieyi")) {
                write("�ܲ�ͨ��ֵؿ����㣬�ʵ�������˭ѽ��\n");
                return  1;
        }

        if (skill != "kongming-quan" && skill != "����ȭ") {
                write("���������±����ұ���ѧ�ˡ�\n");
                return 1;
        }

        my_skill = me->query_skill(skill, 1);
        master_skill = ob->query_skill(skill, 1);
        if( my_skill >= master_skill ) {
                write("���ڿ���ȭ�ϵ������Ѿ���������ͯ�ˣ�\n");
                return 1;
        }

        if( !SKILL_D(skill)->valid_learn(me) ) {
                write("������ǿ��ֲ������㹻���ڹ��������ſ���ѧϰ����ȭ��\n");
                return 1;
        }

        gin_cost = 150 / (int)me->query("int");

        if( !my_skill ) {
                gin_cost *= 2;
                me->set_skill(skill,0);
        }

        rand = random(20);
        if (rand == 4)
                gin_cost *= 2;
        else if (rand == 15)
                gin_cost += 4;
        if( (int)me->query("potential") < 1 ) {
                write("���Ǳ���Ѿ����ӵ������ˣ�û�а취��ѧ�ˡ�\n");
                return 1;
        }

        message_vision("$N��$n����йء�����ȭ�������⡣\n", me, ob);

        if( (int)me->query("jing") > gin_cost ) {
        write("�ܲ�ͨ��������ӡ����¾������о仰��������ֲ��Ϊ���������ޣ�����֮�á��仧���Ϊ�ң������ޣ�����֮�á���\n");
                write("�ܲ�ͨ���ھ����������ȱ�����ò��ף���ӯ���壬���ò��\n");
                if( (string)SKILL_D(skill)->type()=="martial"
                &&      my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) {
                        write("Ҳ����ȱ��ʵս���飬�������ͯ�Ľ��������޷���ᡣ\n");
                } 
                else {
                        if (rand == 13) {
                                write("��������ͼ�������е����ʱ������ͯ��Ȼ�����Աߴ����������ֹ�����˸�ƨ�����ң�������ķ����ҡ�\n");
                                write("�����ʲô��ûѧ����\n");
                                return 1;
                        }
                        else if (rand == 5) {
                                write("�ܲ�ͨ���������䣬��Ȼ���ͷ�������������������������ĸ��˴�ܿɺã���\n");
                                write("�����ֻ��������ˣ��һ��\n");
                                return 1;
                        }
                        else if (rand == 4) {
                                write("��������ͼ�������е����ʱ������ͯ��Ȼ�����Աߴ����������ֹ�����˸�ƨ�����ң�������ķ����ҡ�\n");
                                write("����㻨�˱�ƽ����һ���ľ�����\n");
                        }
                        else if (rand == 15) {
                                write("��������ͼ�������е����ʱ������ͯ��Ȼ�����Աߴ����������ֹ�����˸�ƨ�����ң�������ķ����ҡ�\n");
                                write("����㻨�˱�ƽ����ö�ľ�����\n");
                        }
                        if(skill_name = SKILL_D(skill)->query_skill_name(my_skill))
                                write("����������ͯ��ָ�����ԡ�" + skill_name + "����һ���ƺ���Щ�ĵá�\n");
                        else
                                write("����������ͯ��ָ�����ƺ���Щ�ĵá�\n");
                        me->add("potential", -1);
                        me->improve_skill(skill, random(me->query_int()));
                }
        } 
        else {
                gin_cost = me->query("jing");
                write("�����̫���ˣ����ʲôҲû��ѧ����\n");
        }
        me->receive_damage("jing", gin_cost );
        return 1;
}

void finish(object who)
{
       string msg;
       msg = HIC"�ܲ�ͨ˵����������û��ϵ��������ϰ�������þ�û���˴���ˡ���\n";
       msg+= HIY"�ܲ�ͨ˵��������$N������\n";
       msg+= HIC"�ܲ�ͨ���˵ĵ������컹�ְ�����\n";
       msg+= HIR"$N���书�����������ڳ��ܲ��ˣ����˹�ȥ��\n"; 
/*
       if ((who->query("thd/quest1")<3)&&(who->query_temp("thd/story")==2))
       {
               msg+=HIW"$N�Ͻ���ȫ����ķ���ѧ��������ǿ��ס��������û�ܵ����ˡ�\n"NOR;
               msg+= HIW"�Ժ��У�$N����������׳��Щ��"NOR;
               who->add("con",1);
               who->set("thd/quest1",3);
       }*/ 
       message_vision(msg, who); 
       who->set_temp("thd/onquest",8);
       who->unconcious();
}
