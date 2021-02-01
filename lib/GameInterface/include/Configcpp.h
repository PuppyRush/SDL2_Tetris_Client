//
// Created by chaed on 19. 5. 5.
//

#ifndef GAMEINTERFACE_CONFIGCPP_H
#define GAMEINTERFACE_CONFIGCPP_H

#define _CONSTANCE_VERSION_V1_ 1


#ifndef GI_INLINE
#   if defined(__GNUC__)
#       define GI_INLINE __inline__
#   elif (defined(_MSC_VER) || defined(__BORLANDC__) || \
         defined(__DMC__) || defined(__SC__) || \
         defined(__WATCOMC__) || defined(__LCC__) || \
         defined(__DECC) || defined(__CC_ARM))
#       define GI_INLINE __inline
#       ifndef __inline__
#           define __inline__ __inline
#       endif
#   else
#       define GI_INLINE inline
#       ifndef __inline__
#           define __inline__ inline
#       endif
#   endif
#endif /* GI_INLINE not defined */

#ifndef GI_FORCE_INLINE
#if defined(_MSC_VER)
#define GI_FORCE_INLINE __forceinline
#elif ( (defined(__GNUC__) && (__GNUC__ >= 4)) || defined(__clang__) )
#define GI_FORCE_INLINE __attribute__((always_inline)) static __inline__
#else
#define GI_FORCE_INLINE static GI_INLINE
#endif
#endif /* GI_FORCE_INLINE not defined */

#ifndef SDL_NORETURN
#if defined(__GNUC__)
#define SDL_NORETURN __attribute__((noreturn))
#elif defined(_MSC_VER)
#define SDL_NORETURN __declspec(noreturn)
#else
#define SDL_NORETURN
#endif
#endif /* SDL_NORETURN not defined */

#endif //GI_TETIRS_CLIENT_CONFIGCPP_H
