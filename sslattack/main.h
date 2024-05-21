#ifndef main_h
#define main_h

#include <stddef.h>
#include <stdint.h>
#include <math.h>

#if !defined(MAIN_EXPORT)
#define MAIN_VISIBILITY __attribute__((visibility("hidden")))
#else
#define MAIN_VISIBILITY __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
    
    /*
     * A structure representing a particular intended rebinding from a symbol
     * name to its replacement
     */
    struct rebinding {
        const char *name;
        void *replacement;
        void **replaced;
    };
    
    MAIN_VISIBILITY
    int rebind_symbols(struct rebinding rebindings[], size_t rebindings_nel);
    
    /*
     * Rebinds as above, but only in the specified image. The header should point
     * to the mach-o header, the slide should be the slide offset. Others as above.
     */
    MAIN_VISIBILITY
    int rebind_symbols_image(void *header,
                             intptr_t slide,
                             struct rebinding rebindings[],
                             size_t rebindings_nel);
    
#ifdef __cplusplus
}
#endif //__cplusplus

#endif //main_h
