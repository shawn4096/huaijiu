//by cool 98.6.1
//¸Ä±àÕßcaiji@SJ 8/24/2000
#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;
#include "skill.h";


string *first_name = ({
"ÕÔ","Ç®","Ëï","Àî","ÖÜ","Îâ","Ö£","Íõ","·ë","³Â","ñÒ","ÎÀ",
"½¯","Éò","º«","Ñî","Öì","ÇØ","ÓÈ","Ðí","ºÎ","ÂÀ","Ê©","ÕÅ",
"¿×","²Ü","ÑÏ","»ª","½ð","Îº","ÌÕ","½ª","ÆÝ","Ð»","×Þ","Ó÷",
"°Ø","Ë®","ñ¼","ÕÂ","ÔÆ","ËÕ","ÅË","¸ð","ÞÉ","·¶","Åí","ÀÉ",
"Â³","Î¤","²ý","Âí","Ãç","·ï","»¨","·½","Éµ","ÈÎ","Ô¬","Áø",
"µË","±«","Ê·","ÌÆ","·Ñ","Á®","á¯","Ñ¦","À×","ºØ","Äß","ÌÀ",
"ÌÙ","Òó","ÂÞ","»ª","ºÂ","Úù","°²","³£","ÀÖ","´ô","Ê±","¸¶",
"Æ¤","±å","Æë","¿µ","Îé","Óà","Ôª","²·","¹Ë","Ó¯","Æ½","»Æ",
"ºÍ","ÄÂ","Ð¤","Òü","Ò¦","ÉÛ","Õ¿","Íô","Æî","Ã«","Óí","µÒ",
"Ã×","±´","Ã÷","²Ø","¼Æ","·ü","³É","´÷","Ì¸","ËÎ","Ã©","ÅÓ",
"ÐÜ","¼Í","Êæ","Çü","Ïî","×£","¶­","Áº","·®","ºú","Áè","»ô",
"ÓÝ","Íò","Ö§","¿Â","êÃ","¹Ü","Â¬","Ó¢","³ð","ºò","ÔÀ","Ë§",
"Ë¾Âí","ÉÏ¹Ù","Å·Ñô","ÏÄºò","Öî¸ð","ÎÅÈË","¶«·½","ºÕÁ¬","»Ê¸¦",
"Î¾³Ù","¹«Ñò","å£Ì¨","¹«ÖÎ","×ÚÕþ","å§Ñô","´¾ÓÚ","µ¥ÓÚ","Ì«Êå",
"ÉêÍÀ","¹«Ëï","ÖÙËï","Ô¯Ðù","Áîºü","ÖÓÀë","ÓîÎÄ","³¤Ëï","Ä»ÈÝ",
"Ë¾Í½","Ê¦¿Õ","ò§¿×","¶ËÄ¾","Î×Âí","¹«Î÷","Æáµñ","ÀÖÕý","ÈÀæá",
"¹«Á¼","ÍØÖº","¼Ð¹È","Ô×¸¸","¹ÈÁº","³þ½ú","ÑÖ·¨","ÈêÛ³","Í¿ÇÕ",
"¶ÎÇ§","°ÙÀï","¶«¹ù","ÄÏ¹ù","ºôÑÓ","¹éº£","ÑòÉà","Î¢Éú","ÁºÇð",
"×óÇð","¶«ÃÅ","Î÷ÃÅ","°ÛÉÍ","ÄÏ¹Ù",
"çÃ","¿º","¿ö","ºó","ÓÐ","ÇÙ","ÉÌ","Ä²","ÙÜ","¶ú","Ä«","¹þ",
"ÚÛ","Äê","°®","Ñô","Ù¡","µÚ","Îå","ÑÔ","¸£","Øá","ÖÓ","×Ú",
"ÁÖ","Ê¯",
});

string *first_name_id = ({
"zhao","qian","sun","li","zhou","wu","zhen","wang","feng","chen","zhu","wei",
"jiang","shen","han","yang","zhu","qing","you","xu","he","lu","shi","zhang",
"kong","cao","yan","hua","jin","wei","tao","jiang","qie","xie","zhou","yu",
"bo","shui","dou","zhang","yun","su","pan","ge","xi","fan","peng","lang",
"lu","wei","chang","ma","miao","feng","hua","fang","sha","ren","yuan","liu",
"deng","bao","shi","tang","fei","lian","chen","xue","lei","he","ni","tang",
"teng","yin","luo","hua","hao","wu","an","chang","le","dai","shi","fu",
"pi","bian","qi","kang","wu","yu","yuan","po","gu","ying","ping","huang",
"he","mu","xiao","yin","yao","shao","zhan","wang","qi","mao","yu","di",
"mi","bei","ming","zang","ji","fu","cheng","dai","tan","song","mao","pang",
"xiong","ji","su","qu","xiang","zhu","dong","liang","fan","hu","ling","ho",
"yu","wan","zhi","ke","jiu","guan","lu","ying","qiu","hou","yue","suai",
"sima","shangguan","ouyang","xiahou","zhuge","wenren","dongfang","helian","huangpu",
"weichi","gongyang","zhantai","gongye","zongzheng","puyang","chunyu","shanyu","taishu",
"shentu","gongshun","zhongshun","xuanyuan","linghu","zhongli","yuwen","changshun","murong",
"situ","shikong","zhuankong","duanmu","wuma","gongxi","qidiao","lezheng","xiangsi",
"gongliang","tuozhi","jiagu","zaifu","guliang","chujing","yanfa","ruye","tuqin",
"duanqian","baili","dongguo","nanguo","huyan","guihai","yangshe","weisheng","liangqiu",
"zuoqiu","dongmen","ximen","baishang","nangong",
"gou","kang","kuang","hou","you","qing","shang","mo","she","er","mo","ha",
"qiao","nian","ai","yang","dong","di","wu","yan","fu","kai","zong","zong",
"lin","shi",
});
string *name_words = ({
"ÖÒ","Ð¢","Àñ","Òå","ÖÇ","ÓÂ","ÈÊ","¿ï","ÏÜ","Áî","¸£","Â»","´ó","Ð¡","Ïþ",
"¸ß","¿É","°¢","½ð","ÊÀ","¿Ë","Êå","Ö®","¹«","·ò","Ê±","Èô","Çì","ÎÄ","Îä",
"¶à","²Å","³¤","×Ó","ÓÀ","ÓÑ","×Ô","ÈË","Îª","Ìú","°Ô","°×","°à","±ó","±ö",
"²ý","³¬","³Ï","´¨","¶¦","¶¨","¶·","·¨","·É","·ç","·æ","¸Ö","î¸","¹á","¹â",
"º£","»¢","»ª","ºÆ","ºê","¼Ã","¼á","½¡","½£","½­","½ø","½Ü","¿¡","¿µ","Á¼",
"÷ë","Ãñ","Ã÷","Ãù","Äþ","Åà","Æô","Ç¿","ÈÙ","É½","Ì©","ÌÎ","Í¦","Î°","Îõ",
"Ïé","ÐÛ","Ðñ","Òã","è¤","Óð","Óî","ÔÀ","ÖÛ","°®","´º","µ¤","·¼","·Ò","·ï",
"¹Ã","ºì","ºç","½¿","¾ê","¾Õ","À¼","á°","Àö","Àò","Á«","Áá","ÁÕ","ÄÈ","ÇÙ",
"ÇÛ","Ù»","Æ¼","æÃ","Ï¼","Ïã","ÑÞ","Ñà","Ó¢","çø","Óñ","Õä","Öé",
});

string *name_words_id = ({ "zhong","xiao","li","yi","zhi","yong","ren","kuang",
"xian","ling","fu","lu","da","xiao","xiao","gao","ke","e","jin","shi","ke","shu",
"zhi","gong","fu","shi","ruo","qing","wen","wu","duo","cai","chang","zi","yong",
"you","zi","ren","wei","tie","ba","bai","ban","bin","bin","chang","chao","cheng",
"chuan","ding","ding","dou","fa","fei","feng","feng","gang","gang","guan","guang",
"hai","hu","hua","hao","hong","ji","jian","jian","jian","jiang","jin","jie",
"jun","kang","liang","lin","min","ming","ming","ning","pei","qi","qiang","rong",
"shan","tai","tao","ting","wei","xi","xiang","xiong","xu","yi","yu","yu","yu","yue",
"zhou","ai","chun","dan","fang","fen","feng","gu","hong","hong","jiao","juan","ju",
"lan","lan","li","li","lian","ling","lin","na","qin","qin","qian","ping","ting","xia",
"xiang","yan","yan","ying","ying","yu","zhen","zhu", });

string *color_title = ({HIC+"[ÐþÎä]É±ÊÖ"+NOR,CYN+"[ÖìÈ¸]É±ÊÖ"+NOR,RED+"[°×»¢]É±ÊÖ"+NOR,HIR+"[ÇàÁú]É±ÊÖ"+NOR});
string *k_weapon = ({"sword","blade","staff","whip","gun",});

void create()
{
       int i, j, k;
       string name,name_word;
       i = random(sizeof(first_name));
       name = first_name[i];
       
       j = random(sizeof(name_words));
       name += name_words[j]; 
       name_word = name_words_id[j];

       if( random(10) > 5 ){
               k = random(sizeof(name_words));
               name += name_words[k];
               name_word = name_word + name_words_id[k];
       }

       set_name(name, ({ first_name_id[i]+" "+name_word, first_name_id[i], name_word}) );
       set("title", color_title[random(sizeof(color_title))]);
       set("gender", random(3)?"ÄÐÐÔ":"Å®ÐÔ");
       set("long", "ÕâÈËÉí´©ºÚÉ«½ô×°£¬ÃæÉÏÃÉ×ÅÒ»¿éºÚ²¼£¬Ö»Â¶³öÒ»Ë«ÑÛ¾¦£¬¾«¹âËÄÉä¡£\n");
       set("age", random(10)+24);      
       set("str", 15+random(5));
       set("int",20+random(5));  
       set("con",20+random(5));     
       set("dex",20+random(5));
       set("combat_exp", 100000);
       set("no_quest", 1);   
       set("shen_type", 1);
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
add_money("silver", random(50)+50);

//carry_object("/u/cool/dalijob/obj/"+weapon)->wield();
carry_object("/d/dali/obj/blackcloth")->wear();

}
#include "shashou.h";
